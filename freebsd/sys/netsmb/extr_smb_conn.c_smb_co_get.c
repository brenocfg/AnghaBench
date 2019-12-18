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
struct smb_connobj {int /*<<< orphan*/  co_usecount; int /*<<< orphan*/  co_interlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int) ; 
 scalar_t__ curthread ; 
 int smb_co_lock (struct smb_connobj*) ; 
 scalar_t__ sx_xholder (int /*<<< orphan*/ *) ; 

int
smb_co_get(struct smb_connobj *cp, struct smb_cred *scred)
{
	int error;

	MPASS(sx_xholder(&cp->co_interlock) == curthread);
	cp->co_usecount++;
	error = smb_co_lock(cp);
	if (error) 
		cp->co_usecount--;
	return error;
}