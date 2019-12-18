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
typedef  int /*<<< orphan*/  u_int16_t ;
struct nbns_rq {int nr_opcode; scalar_t__ nr_trnid; struct nb_ctx* nr_nbd; int /*<<< orphan*/  nr_rq; } ;
struct nb_ctx {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  NBDG_MAXSIZE ; 
 int /*<<< orphan*/  bzero (struct nbns_rq*,int) ; 
 int /*<<< orphan*/  free (struct nbns_rq*) ; 
 struct nbns_rq* malloc (int) ; 
 int mb_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
nbns_rq_create(int opcode, struct nb_ctx *ctx, struct nbns_rq **rqpp)
{
	struct nbns_rq *rqp;
	static u_int16_t trnid;
	int error;

	rqp = malloc(sizeof(*rqp));
	if (rqp == NULL)
		return ENOMEM;
	bzero(rqp, sizeof(*rqp));
	error = mb_init(&rqp->nr_rq, NBDG_MAXSIZE);
	if (error) {
		free(rqp);
		return error;
	}
	rqp->nr_opcode = opcode;
	rqp->nr_nbd = ctx;
	rqp->nr_trnid = trnid++;
	*rqpp = rqp;
	return 0;
}