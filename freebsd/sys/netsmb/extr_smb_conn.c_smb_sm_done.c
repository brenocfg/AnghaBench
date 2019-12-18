#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int co_usecount; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  SMBERROR (char*,int) ; 
 int /*<<< orphan*/  smb_co_done (TYPE_1__*) ; 
 TYPE_1__ smb_vclist ; 

int
smb_sm_done(void)
{

	/* XXX: hold the mutex */
	if (smb_vclist.co_usecount > 1) {
		SMBERROR("%d connections still active\n", smb_vclist.co_usecount - 1);
		return EBUSY;
	}
	smb_co_done(&smb_vclist);
	return 0;
}