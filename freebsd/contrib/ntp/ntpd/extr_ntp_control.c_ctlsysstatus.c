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
typedef  int /*<<< orphan*/  u_short ;
typedef  scalar_t__ u_char ;
struct TYPE_2__ {scalar_t__ sstclktype; size_t refclktype; } ;

/* Variables and functions */
 size_t COUNTOF (scalar_t__*) ; 
 scalar_t__ CTL_SST_TS_NTP ; 
 scalar_t__ CTL_SST_TS_UNSPEC ; 
 int /*<<< orphan*/  CTL_SYS_STATUS (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__* clocktypes ; 
 int /*<<< orphan*/  ctl_sys_last_event ; 
 int /*<<< orphan*/  ctl_sys_num_events ; 
 int /*<<< orphan*/  sys_leap ; 
 TYPE_1__* sys_peer ; 

u_short
ctlsysstatus(void)
{
	register u_char this_clock;

	this_clock = CTL_SST_TS_UNSPEC;
#ifdef REFCLOCK
	if (sys_peer != NULL) {
		if (CTL_SST_TS_UNSPEC != sys_peer->sstclktype)
			this_clock = sys_peer->sstclktype;
		else if (sys_peer->refclktype < COUNTOF(clocktypes))
			this_clock = clocktypes[sys_peer->refclktype];
	}
#else /* REFCLOCK */
	if (sys_peer != 0)
		this_clock = CTL_SST_TS_NTP;
#endif /* REFCLOCK */
	return CTL_SYS_STATUS(sys_leap, this_clock, ctl_sys_num_events,
			      ctl_sys_last_event);
}