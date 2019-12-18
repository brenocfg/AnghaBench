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
struct smb_cred {int dummy; } ;
struct smb_connobj {int co_usecount; int /*<<< orphan*/  co_interlock; int /*<<< orphan*/  co_flags; int /*<<< orphan*/  co_level; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMBERROR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMBO_GONE ; 
 int /*<<< orphan*/  smb_co_gone (struct smb_connobj*,struct smb_cred*) ; 
 int /*<<< orphan*/  smb_co_unlock (struct smb_connobj*) ; 
 int /*<<< orphan*/  sx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 

void
smb_co_rele(struct smb_connobj *cp, struct smb_cred *scred)
{

	sx_xlock(&cp->co_interlock);
	smb_co_unlock(cp);
	if (cp->co_usecount > 1) {
		cp->co_usecount--;
		sx_unlock(&cp->co_interlock);
		return;
	}
	if (cp->co_usecount == 0) {
		SMBERROR("negative use_count for object %d", cp->co_level);
		sx_unlock(&cp->co_interlock);
		return;
	}
	cp->co_usecount--;
	cp->co_flags |= SMBO_GONE;
	sx_unlock(&cp->co_interlock);
	smb_co_gone(cp, scred);
}