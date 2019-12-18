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
struct smb_rq {int sr_flags; TYPE_1__* sr_cred; } ;
struct TYPE_2__ {int /*<<< orphan*/  scr_td; } ;

/* Variables and functions */
 int EINTR ; 
 int SMBR_INTR ; 
 int smb_td_intr (int /*<<< orphan*/ ) ; 

int
smb_rq_intr(struct smb_rq *rqp)
{
	if (rqp->sr_flags & SMBR_INTR)
		return EINTR;
	return smb_td_intr(rqp->sr_cred->scr_td);
}