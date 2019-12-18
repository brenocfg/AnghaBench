#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct smb_vc {int vc_txmax; int /*<<< orphan*/  vc_iod; } ;
struct mdchain {struct mbuf* md_top; } ;
struct TYPE_4__ {struct mbuf* mb_top; } ;
struct TYPE_3__ {struct mbuf* mb_top; } ;
struct smb_t2rq {int t2_maxpcount; int t2_maxdcount; int t2_maxscount; int t2_setupcount; int* t2_setupdata; int t2_fid; struct mdchain t2_rdata; struct mdchain t2_rparam; int /*<<< orphan*/  t2_flags; int /*<<< orphan*/ * t_name; struct smb_rq* t2_rq; int /*<<< orphan*/  t2_source; TYPE_2__ t2_tdata; TYPE_1__ t2_tparam; struct smb_cred* t2_cred; struct smb_vc* t2_vc; } ;
struct mbchain {int dummy; } ;
struct smb_rq {int sr_flags; int /*<<< orphan*/  sr_state; struct mbchain sr_rq; struct smb_t2rq* sr_t2; } ;
struct smb_cred {int dummy; } ;
struct mbuf {int dummy; } ;

/* Variables and functions */
 int ALIGN4 (int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  MB_MSYSTEM ; 
 int /*<<< orphan*/  MB_MZERO ; 
 int /*<<< orphan*/  SMBIOD_EV_NEWRQ ; 
 int /*<<< orphan*/  SMBRQ_NOTSENT ; 
 int SMBR_MULTIPACKET ; 
 int SMBR_RESTART ; 
 int /*<<< orphan*/  SMBSDEBUG (char*,int,int,int) ; 
 int /*<<< orphan*/  SMBT2_ALLSENT ; 
 int /*<<< orphan*/  SMBT2_RESTART ; 
 int /*<<< orphan*/  SMBT2_SECONDARY ; 
 int /*<<< orphan*/  SMB_COM_TRANSACTION ; 
 int /*<<< orphan*/  SMB_COM_TRANSACTION2 ; 
 int /*<<< orphan*/  SMB_COM_TRANSACTION2_SECONDARY ; 
 int /*<<< orphan*/  SMB_COM_TRANSACTION_SECONDARY ; 
 int m_fixhdr (struct mbuf*) ; 
 int mb_fixhdr (struct mbchain*) ; 
 int /*<<< orphan*/  mb_put_mbuf (struct mbchain*,struct mbuf*) ; 
 int /*<<< orphan*/  mb_put_mem (struct mbchain*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb_put_uint16le (struct mbchain*,int) ; 
 int /*<<< orphan*/  mb_put_uint32le (struct mbchain*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb_put_uint8 (struct mbchain*,int) ; 
 int /*<<< orphan*/  md_done (struct mdchain*) ; 
 int md_get_mbuf (struct mdchain*,int,struct mbuf**) ; 
 int /*<<< orphan*/  md_initm (struct mdchain*,struct mbuf*) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  smb_iod_removerq (struct smb_rq*) ; 
 int smb_iod_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int smb_rq_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct smb_cred*,struct smb_rq**) ; 
 int /*<<< orphan*/  smb_rq_bend (struct smb_rq*) ; 
 int /*<<< orphan*/  smb_rq_bstart (struct smb_rq*) ; 
 int /*<<< orphan*/  smb_rq_done (struct smb_rq*) ; 
 int smb_rq_enqueue (struct smb_rq*) ; 
 int smb_rq_new (struct smb_rq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smb_rq_wend (struct smb_rq*) ; 
 int /*<<< orphan*/  smb_rq_wstart (struct smb_rq*) ; 
 int smb_t2_reply (struct smb_t2rq*) ; 
 int strlen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
smb_t2_request_int(struct smb_t2rq *t2p)
{
	struct smb_vc *vcp = t2p->t2_vc;
	struct smb_cred *scred = t2p->t2_cred;
	struct mbchain *mbp;
	struct mdchain *mdp, mbparam, mbdata;
	struct mbuf *m;
	struct smb_rq *rqp;
	int totpcount, leftpcount, totdcount, leftdcount, len, txmax, i;
	int error, doff, poff, txdcount, txpcount, nmlen;

	m = t2p->t2_tparam.mb_top;
	if (m) {
		md_initm(&mbparam, m);	/* do not free it! */
		totpcount = m_fixhdr(m);
		if (totpcount > 0xffff)		/* maxvalue for u_short */
			return EINVAL;
	} else
		totpcount = 0;
	m = t2p->t2_tdata.mb_top;
	if (m) {
		md_initm(&mbdata, m);	/* do not free it! */
		totdcount =  m_fixhdr(m);
		if (totdcount > 0xffff)
			return EINVAL;
	} else
		totdcount = 0;
	leftdcount = totdcount;
	leftpcount = totpcount;
	txmax = vcp->vc_txmax;
	error = smb_rq_alloc(t2p->t2_source, t2p->t_name ?
	    SMB_COM_TRANSACTION : SMB_COM_TRANSACTION2, scred, &rqp);
	if (error)
		return error;
	rqp->sr_flags |= SMBR_MULTIPACKET;
	t2p->t2_rq = rqp;
	rqp->sr_t2 = t2p;
	mbp = &rqp->sr_rq;
	smb_rq_wstart(rqp);
	mb_put_uint16le(mbp, totpcount);
	mb_put_uint16le(mbp, totdcount);
	mb_put_uint16le(mbp, t2p->t2_maxpcount);
	mb_put_uint16le(mbp, t2p->t2_maxdcount);
	mb_put_uint8(mbp, t2p->t2_maxscount);
	mb_put_uint8(mbp, 0);			/* reserved */
	mb_put_uint16le(mbp, 0);			/* flags */
	mb_put_uint32le(mbp, 0);			/* Timeout */
	mb_put_uint16le(mbp, 0);			/* reserved 2 */
	len = mb_fixhdr(mbp);
	/*
	 * now we have known packet size as
	 * ALIGN4(len + 5 * 2 + setupcount * 2 + 2 + strlen(name) + 1),
	 * and need to decide which parts should go into the first request
	 */
	nmlen = t2p->t_name ? strlen(t2p->t_name) : 0;
	len = ALIGN4(len + 5 * 2 + t2p->t2_setupcount * 2 + 2 + nmlen + 1);
	if (len + leftpcount > txmax) {
		txpcount = min(leftpcount, txmax - len);
		poff = len;
		txdcount = 0;
		doff = 0;
	} else {
		txpcount = leftpcount;
		poff = txpcount ? len : 0;
		len = ALIGN4(len + txpcount);
		txdcount = min(leftdcount, txmax - len);
		doff = txdcount ? len : 0;
	}
	leftpcount -= txpcount;
	leftdcount -= txdcount;
	mb_put_uint16le(mbp, txpcount);
	mb_put_uint16le(mbp, poff);
	mb_put_uint16le(mbp, txdcount);
	mb_put_uint16le(mbp, doff);
	mb_put_uint8(mbp, t2p->t2_setupcount);
	mb_put_uint8(mbp, 0);
	for (i = 0; i < t2p->t2_setupcount; i++)
		mb_put_uint16le(mbp, t2p->t2_setupdata[i]);
	smb_rq_wend(rqp);
	smb_rq_bstart(rqp);
	/* TDUNICODE */
	if (t2p->t_name)
		mb_put_mem(mbp, t2p->t_name, nmlen, MB_MSYSTEM);
	mb_put_uint8(mbp, 0);	/* terminating zero */
	len = mb_fixhdr(mbp);
	if (txpcount) {
		mb_put_mem(mbp, NULL, ALIGN4(len) - len, MB_MZERO);
		error = md_get_mbuf(&mbparam, txpcount, &m);
		SMBSDEBUG("%d:%d:%d\n", error, txpcount, txmax);
		if (error)
			goto freerq;
		mb_put_mbuf(mbp, m);
	}
	len = mb_fixhdr(mbp);
	if (txdcount) {
		mb_put_mem(mbp, NULL, ALIGN4(len) - len, MB_MZERO);
		error = md_get_mbuf(&mbdata, txdcount, &m);
		if (error)
			goto freerq;
		mb_put_mbuf(mbp, m);
	}
	smb_rq_bend(rqp);	/* incredible, but thats it... */
	error = smb_rq_enqueue(rqp);
	if (error)
		goto freerq;
	if (leftpcount == 0 && leftdcount == 0)
		t2p->t2_flags |= SMBT2_ALLSENT;
	error = smb_t2_reply(t2p);
	if (error)
		goto bad;
	while (leftpcount || leftdcount) {
		t2p->t2_flags |= SMBT2_SECONDARY;
		error = smb_rq_new(rqp, t2p->t_name ? 
		    SMB_COM_TRANSACTION_SECONDARY : SMB_COM_TRANSACTION2_SECONDARY);
		if (error)
			goto bad;
		mbp = &rqp->sr_rq;
		smb_rq_wstart(rqp);
		mb_put_uint16le(mbp, totpcount);
		mb_put_uint16le(mbp, totdcount);
		len = mb_fixhdr(mbp);
		/*
		 * now we have known packet size as
		 * ALIGN4(len + 7 * 2 + 2) for T2 request, and -2 for T one,
		 * and need to decide which parts should go into request
		 */
		len = ALIGN4(len + 6 * 2 + 2);
		if (t2p->t_name == NULL)
			len += 2;
		if (len + leftpcount > txmax) {
			txpcount = min(leftpcount, txmax - len);
			poff = len;
			txdcount = 0;
			doff = 0;
		} else {
			txpcount = leftpcount;
			poff = txpcount ? len : 0;
			len = ALIGN4(len + txpcount);
			txdcount = min(leftdcount, txmax - len);
			doff = txdcount ? len : 0;
		}
		mb_put_uint16le(mbp, txpcount);
		mb_put_uint16le(mbp, poff);
		mb_put_uint16le(mbp, totpcount - leftpcount);
		mb_put_uint16le(mbp, txdcount);
		mb_put_uint16le(mbp, doff);
		mb_put_uint16le(mbp, totdcount - leftdcount);
		leftpcount -= txpcount;
		leftdcount -= txdcount;
		if (t2p->t_name == NULL)
			mb_put_uint16le(mbp, t2p->t2_fid);
		smb_rq_wend(rqp);
		smb_rq_bstart(rqp);
		mb_put_uint8(mbp, 0);	/* name */
		len = mb_fixhdr(mbp);
		if (txpcount) {
			mb_put_mem(mbp, NULL, ALIGN4(len) - len, MB_MZERO);
			error = md_get_mbuf(&mbparam, txpcount, &m);
			if (error)
				goto bad;
			mb_put_mbuf(mbp, m);
		}
		len = mb_fixhdr(mbp);
		if (txdcount) {
			mb_put_mem(mbp, NULL, ALIGN4(len) - len, MB_MZERO);
			error = md_get_mbuf(&mbdata, txdcount, &m);
			if (error)
				goto bad;
			mb_put_mbuf(mbp, m);
		}
		smb_rq_bend(rqp);
		rqp->sr_state = SMBRQ_NOTSENT;
		error = smb_iod_request(vcp->vc_iod, SMBIOD_EV_NEWRQ, NULL);
		if (error)
			goto bad;
	}	/* while left params or data */
	t2p->t2_flags |= SMBT2_ALLSENT;
	mdp = &t2p->t2_rdata;
	if (mdp->md_top) {
		m_fixhdr(mdp->md_top);
		md_initm(mdp, mdp->md_top);
	}
	mdp = &t2p->t2_rparam;
	if (mdp->md_top) {
		m_fixhdr(mdp->md_top);
		md_initm(mdp, mdp->md_top);
	}
bad:
	smb_iod_removerq(rqp);
freerq:
	smb_rq_done(rqp);
	if (error) {
		if (rqp->sr_flags & SMBR_RESTART)
			t2p->t2_flags |= SMBT2_RESTART;
		md_done(&t2p->t2_rparam);
		md_done(&t2p->t2_rdata);
	}
	return error;
}