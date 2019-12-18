#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  co_interlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMBL_SM ; 
 int /*<<< orphan*/  smb_co_init (TYPE_1__*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  smb_co_unlock (TYPE_1__*) ; 
 TYPE_1__ smb_vclist ; 
 int /*<<< orphan*/  sx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 

int
smb_sm_init(void)
{

	smb_co_init(&smb_vclist, SMBL_SM, "smbsm ilock", "smbsm");
	sx_xlock(&smb_vclist.co_interlock);
	smb_co_unlock(&smb_vclist);
	sx_unlock(&smb_vclist.co_interlock);
	return 0;
}