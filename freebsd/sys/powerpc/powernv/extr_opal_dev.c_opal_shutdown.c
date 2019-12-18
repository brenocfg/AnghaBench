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
 int /*<<< orphan*/  OPAL_CEC_POWER_DOWN ; 
 int /*<<< orphan*/  OPAL_CEC_REBOOT ; 
 int /*<<< orphan*/  OPAL_RETURN_CPU ; 
 int RB_HALT ; 
 int /*<<< orphan*/  opal_call (int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void
opal_shutdown(void *arg, int howto)
{

	if (howto & RB_HALT)
		opal_call(OPAL_CEC_POWER_DOWN, 0 /* Normal power off */);
	else
		opal_call(OPAL_CEC_REBOOT);

	opal_call(OPAL_RETURN_CPU);
}