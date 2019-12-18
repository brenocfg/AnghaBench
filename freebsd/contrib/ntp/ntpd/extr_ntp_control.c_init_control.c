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
struct TYPE_3__ {scalar_t__ tr_flags; } ;

/* Variables and functions */
 size_t COUNTOF (TYPE_1__*) ; 
 int /*<<< orphan*/  EVNT_UNSPEC ; 
 scalar_t__ ctl_auth_keyid ; 
 int /*<<< orphan*/  ctl_clr_stats () ; 
 int /*<<< orphan*/  ctl_sys_last_event ; 
 scalar_t__ ctl_sys_num_events ; 
 TYPE_1__* ctl_traps ; 
 scalar_t__ num_ctl_traps ; 
 int /*<<< orphan*/  uname (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  utsnamebuf ; 

void
init_control(void)
{
	size_t i;

#ifdef HAVE_UNAME
	uname(&utsnamebuf);
#endif /* HAVE_UNAME */

	ctl_clr_stats();

	ctl_auth_keyid = 0;
	ctl_sys_last_event = EVNT_UNSPEC;
	ctl_sys_num_events = 0;

	num_ctl_traps = 0;
	for (i = 0; i < COUNTOF(ctl_traps); i++)
		ctl_traps[i].tr_flags = 0;
}