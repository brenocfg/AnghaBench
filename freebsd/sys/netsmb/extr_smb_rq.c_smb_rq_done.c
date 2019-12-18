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
struct smb_rq {int sr_flags; int /*<<< orphan*/  sr_slock; int /*<<< orphan*/  sr_rp; int /*<<< orphan*/  sr_rq; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_SMBRQ ; 
 int SMBR_ALLOCED ; 
 int /*<<< orphan*/  free (struct smb_rq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  md_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smb_sl_destroy (int /*<<< orphan*/ *) ; 

void
smb_rq_done(struct smb_rq *rqp)
{
	mb_done(&rqp->sr_rq);
	md_done(&rqp->sr_rp);
	smb_sl_destroy(&rqp->sr_slock);
	if (rqp->sr_flags & SMBR_ALLOCED)
		free(rqp, M_SMBRQ);
}