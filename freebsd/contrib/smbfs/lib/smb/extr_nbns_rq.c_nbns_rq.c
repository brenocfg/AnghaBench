#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int8_t ;
typedef  scalar_t__ u_int16_t ;
struct mbdata {int mb_count; } ;
struct nbns_rq {int nr_nmflags; scalar_t__ nr_trnid; int nr_rpnmflags; int nr_rprcode; scalar_t__ nr_rpancount; scalar_t__ nr_rpnscount; scalar_t__ nr_rparcount; struct mbdata nr_rp; int /*<<< orphan*/  nr_fd; TYPE_1__* nr_if; struct mbdata nr_rq; } ;
struct TYPE_2__ {struct TYPE_2__* id_next; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int NBERROR (int) ; 
 int NBERR_INVALIDRESPONSE ; 
 int NBNS_NMFLAG_BCAST ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb_get_uint16be (struct mbdata*,scalar_t__*) ; 
 int /*<<< orphan*/  mb_get_uint8 (struct mbdata*,int*) ; 
 TYPE_1__* nb_iflist ; 
 int nbns_rq_opensocket (struct nbns_rq*) ; 
 int nbns_rq_recv (struct nbns_rq*) ; 
 int nbns_rq_send (struct nbns_rq*) ; 

int
nbns_rq(struct nbns_rq *rqp)
{
	struct mbdata *mbp = &rqp->nr_rq;
	u_int16_t rpid;
	u_int8_t nmflags;
	int error, retrycount;

	rqp->nr_if = nb_iflist;
again:
	error = nbns_rq_opensocket(rqp);
	if (error)
		return error;
	retrycount = 3;	/* XXX - configurable */
	for (;;) {
		error = nbns_rq_send(rqp);
		if (error)
			return error;
		error = nbns_rq_recv(rqp);
		if (error) {
			if (error != ETIMEDOUT || retrycount == 0) {
				if ((rqp->nr_nmflags & NBNS_NMFLAG_BCAST) &&
				    rqp->nr_if != NULL &&
				    rqp->nr_if->id_next != NULL) {
					rqp->nr_if = rqp->nr_if->id_next;
					close(rqp->nr_fd);
					goto again;
				} else
					return error;
			}
			retrycount--;
			continue;
		}
		mbp = &rqp->nr_rp;
		if (mbp->mb_count < 12)
			return NBERROR(NBERR_INVALIDRESPONSE);
		mb_get_uint16be(mbp, &rpid);
		if (rpid != rqp->nr_trnid)
			return NBERROR(NBERR_INVALIDRESPONSE);
		break;
	}
	mb_get_uint8(mbp, &nmflags);
	rqp->nr_rpnmflags = (nmflags & 7) << 4;
	mb_get_uint8(mbp, &nmflags);
	rqp->nr_rpnmflags |= (nmflags & 0xf0) >> 4;
	rqp->nr_rprcode = nmflags & 0xf;
	if (rqp->nr_rprcode)
		return NBERROR(rqp->nr_rprcode);
	mb_get_uint16be(mbp, &rpid);	/* QDCOUNT */
	mb_get_uint16be(mbp, &rqp->nr_rpancount);
	mb_get_uint16be(mbp, &rqp->nr_rpnscount);
	mb_get_uint16be(mbp, &rqp->nr_rparcount);
	return 0;
}