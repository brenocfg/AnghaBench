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

/* Variables and functions */
 int /*<<< orphan*/  timeEndPeriod (scalar_t__) ; 
 scalar_t__ timerResolution ; 

void Sys_PlatformExit( void )
{
#ifndef DEDICATED
	if(timerResolution)
		timeEndPeriod(timerResolution);
#endif
}