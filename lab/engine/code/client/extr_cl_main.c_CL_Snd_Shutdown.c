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
struct TYPE_2__ {int /*<<< orphan*/  soundStarted; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_Shutdown () ; 
 TYPE_1__ cls ; 
 int /*<<< orphan*/  qfalse ; 

void CL_Snd_Shutdown(void)
{
	S_Shutdown();
	cls.soundStarted = qfalse;
}