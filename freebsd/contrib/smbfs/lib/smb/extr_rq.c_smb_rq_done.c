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
struct smb_rq {int /*<<< orphan*/  rq_rq; int /*<<< orphan*/  rq_rp; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct smb_rq*) ; 
 int /*<<< orphan*/  mb_done (int /*<<< orphan*/ *) ; 

void
smb_rq_done(struct smb_rq *rqp)
{
	mb_done(&rqp->rq_rp);
	mb_done(&rqp->rq_rq);
	free(rqp);
}