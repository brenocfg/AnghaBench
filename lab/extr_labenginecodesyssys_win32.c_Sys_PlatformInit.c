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
typedef  int /*<<< orphan*/  ptc ;
struct TYPE_3__ {int wPeriodMin; } ;
typedef  TYPE_1__ TIMECAPS ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Printf (char*,int) ; 
 scalar_t__ MMSYSERR_NOERROR ; 
 int /*<<< orphan*/  Sys_SetFloatEnv () ; 
 int /*<<< orphan*/  timeBeginPeriod (int) ; 
 scalar_t__ timeGetDevCaps (TYPE_1__*,int) ; 
 int timerResolution ; 

void Sys_PlatformInit( void )
{
#ifndef DEDICATED
	TIMECAPS ptc;
#endif

	Sys_SetFloatEnv();

#ifndef DEDICATED
	if(timeGetDevCaps(&ptc, sizeof(ptc)) == MMSYSERR_NOERROR)
	{
		timerResolution = ptc.wPeriodMin;

		if(timerResolution > 1)
		{
			Com_Printf("Warning: Minimum supported timer resolution is %ums "
				"on this system, recommended resolution 1ms\n", timerResolution);
		}
		
		timeBeginPeriod(timerResolution);				
	}
	else
		timerResolution = 0;
#endif
}