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
struct clock_event_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AU1000_SYS_CNTRCTRL ; 
 int /*<<< orphan*/  AU1000_SYS_RTCMATCH2 ; 
 int /*<<< orphan*/  AU1000_SYS_RTCREAD ; 
 int SYS_CNTRL_M21 ; 
 int alchemy_rdsys (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alchemy_wrsys (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int au1x_rtcmatch2_set_next_event(unsigned long delta,
					 struct clock_event_device *cd)
{
	delta += alchemy_rdsys(AU1000_SYS_RTCREAD);
	/* wait for register access */
	while (alchemy_rdsys(AU1000_SYS_CNTRCTRL) & SYS_CNTRL_M21)
		;
	alchemy_wrsys(delta, AU1000_SYS_RTCMATCH2);

	return 0;
}