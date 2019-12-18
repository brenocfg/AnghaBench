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
 int /*<<< orphan*/  CL_Snd_Shutdown () ; 
 int /*<<< orphan*/  CL_Vid_Restart_f () ; 

void CL_Snd_Restart_f(void)
{
	CL_Snd_Shutdown();
	// sound will be reinitialized by vid_restart
	CL_Vid_Restart_f();
}