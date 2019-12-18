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
struct smb_share {int dummy; } ;
struct smb_connobj {int /*<<< orphan*/  co_interlock; } ;

/* Variables and functions */
 struct smb_connobj* SSTOCP (struct smb_share*) ; 
 int smb_co_lock (struct smb_connobj*) ; 
 int /*<<< orphan*/  sx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 

int
smb_share_lock(struct smb_share *ssp)
{
	struct smb_connobj *cp;
	int error;
	
	cp = SSTOCP(ssp);
	sx_xlock(&cp->co_interlock);
	error = smb_co_lock(cp);
	sx_unlock(&cp->co_interlock);
	return error;
}