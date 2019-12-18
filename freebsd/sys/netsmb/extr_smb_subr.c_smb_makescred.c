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
struct ucred {int dummy; } ;
struct thread {struct ucred* td_ucred; } ;
struct smb_cred {struct ucred* scr_cred; struct thread* scr_td; } ;

/* Variables and functions */

void
smb_makescred(struct smb_cred *scred, struct thread *td, struct ucred *cred)
{
	if (td) {
		scred->scr_td = td;
		scred->scr_cred = cred ? cred : td->td_ucred;
	} else {
		scred->scr_td = NULL;
		scred->scr_cred = cred ? cred : NULL;
	}
}