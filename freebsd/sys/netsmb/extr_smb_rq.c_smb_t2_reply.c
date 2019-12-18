#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u_int8_t ;
typedef  scalar_t__ u_int16_t ;
struct smb_t2rq {int t2_flags; int /*<<< orphan*/  t2_rparam; int /*<<< orphan*/  t2_rdata; struct smb_rq* t2_rq; } ;
struct mdchain {int /*<<< orphan*/  md_top; } ;
struct smb_rq {struct mdchain sr_rp; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  SMBERROR (char*,...) ; 
 int /*<<< orphan*/  SMBRQ_SLOCK (struct smb_rq*) ; 
 int /*<<< orphan*/  SMBRQ_SUNLOCK (struct smb_rq*) ; 
 int SMBT2_ALLRECV ; 
 int SMBT2_ALLSENT ; 
 int /*<<< orphan*/  m_dumpm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  md_get_uint16 (struct mdchain*,int /*<<< orphan*/ *) ; 
 int md_get_uint16le (struct mdchain*,scalar_t__*) ; 
 int md_get_uint8 (struct mdchain*,int*) ; 
 int /*<<< orphan*/  md_next_record (struct mdchain*) ; 
 int smb_rq_reply (struct smb_rq*) ; 
 int smb_t2_placedata (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
smb_t2_reply(struct smb_t2rq *t2p)
{
	struct mdchain *mdp;
	struct smb_rq *rqp = t2p->t2_rq;
	int error, totpgot, totdgot;
	u_int16_t totpcount, totdcount, pcount, poff, doff, pdisp, ddisp;
	u_int16_t tmp, bc, dcount;
	u_int8_t wc;

	error = smb_rq_reply(rqp);
	if (error)
		return error;
	if ((t2p->t2_flags & SMBT2_ALLSENT) == 0) {
		/* 
		 * this is an interim response, ignore it.
		 */
		SMBRQ_SLOCK(rqp);
		md_next_record(&rqp->sr_rp);
		SMBRQ_SUNLOCK(rqp);
		return 0;
	}
	/*
	 * Now we have to get all subsequent responses. The CIFS specification
	 * says that they can be disordered which is weird.
	 * TODO: timo
	 */
	totpgot = totdgot = 0;
	totpcount = totdcount = 0xffff;
	mdp = &rqp->sr_rp;
	for (;;) {
		m_dumpm(mdp->md_top);
		if ((error = md_get_uint8(mdp, &wc)) != 0)
			break;
		if (wc < 10) {
			error = ENOENT;
			break;
		}
		if ((error = md_get_uint16le(mdp, &tmp)) != 0)
			break;
		if (totpcount > tmp)
			totpcount = tmp;
		md_get_uint16le(mdp, &tmp);
		if (totdcount > tmp)
			totdcount = tmp;
		if ((error = md_get_uint16le(mdp, &tmp)) != 0 || /* reserved */
		    (error = md_get_uint16le(mdp, &pcount)) != 0 ||
		    (error = md_get_uint16le(mdp, &poff)) != 0 ||
		    (error = md_get_uint16le(mdp, &pdisp)) != 0)
			break;
		if (pcount != 0 && pdisp != totpgot) {
			SMBERROR("Can't handle disordered parameters %d:%d\n",
			    pdisp, totpgot);
			error = EINVAL;
			break;
		}
		if ((error = md_get_uint16le(mdp, &dcount)) != 0 ||
		    (error = md_get_uint16le(mdp, &doff)) != 0 ||
		    (error = md_get_uint16le(mdp, &ddisp)) != 0)
			break;
		if (dcount != 0 && ddisp != totdgot) {
			SMBERROR("Can't handle disordered data\n");
			error = EINVAL;
			break;
		}
		md_get_uint8(mdp, &wc);
		md_get_uint8(mdp, NULL);
		tmp = wc;
		while (tmp--)
			md_get_uint16(mdp, NULL);
		if ((error = md_get_uint16le(mdp, &bc)) != 0)
			break;
/*		tmp = SMB_HDRLEN + 1 + 10 * 2 + 2 * wc + 2;*/
		if (dcount) {
			error = smb_t2_placedata(mdp->md_top, doff, dcount,
			    &t2p->t2_rdata);
			if (error)
				break;
		}
		if (pcount) {
			error = smb_t2_placedata(mdp->md_top, poff, pcount,
			    &t2p->t2_rparam);
			if (error)
				break;
		}
		totpgot += pcount;
		totdgot += dcount;
		if (totpgot >= totpcount && totdgot >= totdcount) {
			error = 0;
			t2p->t2_flags |= SMBT2_ALLRECV;
			break;
		}
		/*
		 * We're done with this reply, look for the next one.
		 */
		SMBRQ_SLOCK(rqp);
		md_next_record(&rqp->sr_rp);
		SMBRQ_SUNLOCK(rqp);
		error = smb_rq_reply(rqp);
		if (error)
			break;
	}
	return error;
}