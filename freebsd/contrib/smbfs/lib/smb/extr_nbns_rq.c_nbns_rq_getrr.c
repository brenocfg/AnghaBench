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
typedef  int /*<<< orphan*/  u_char ;
struct nbns_rr {int rr_type; int rr_class; int rr_rdlength; int /*<<< orphan*/ * rr_data; int /*<<< orphan*/  rr_ttl; int /*<<< orphan*/ * rr_name; } ;
struct mbdata {int /*<<< orphan*/ * mb_pos; } ;
struct nbns_rq {struct mbdata nr_rp; } ;

/* Variables and functions */
 int NBERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NBERR_INVALIDRESPONSE ; 
 int /*<<< orphan*/  bzero (struct nbns_rr*,int) ; 
 int mb_get_mem (struct mbdata*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mb_get_uint16be (struct mbdata*,int*) ; 
 int /*<<< orphan*/  mb_get_uint32be (struct mbdata*,int /*<<< orphan*/ *) ; 
 int nb_encname_len (int /*<<< orphan*/ *) ; 

int
nbns_rq_getrr(struct nbns_rq *rqp, struct nbns_rr *rrp)
{
	struct mbdata *mbp = &rqp->nr_rp;
	u_char *cp;
	int error, len;

	bzero(rrp, sizeof(*rrp));
	cp = mbp->mb_pos;
	len = nb_encname_len(cp);
	if (len < 1)
		return NBERROR(NBERR_INVALIDRESPONSE);
	rrp->rr_name = cp;
	error = mb_get_mem(mbp, NULL, len);
	if (error)
		return error;
	mb_get_uint16be(mbp, &rrp->rr_type);
	mb_get_uint16be(mbp, &rrp->rr_class);
	mb_get_uint32be(mbp, &rrp->rr_ttl);
	mb_get_uint16be(mbp, &rrp->rr_rdlength);
	rrp->rr_data = mbp->mb_pos;
	error = mb_get_mem(mbp, NULL, rrp->rr_rdlength);
	return error;
}