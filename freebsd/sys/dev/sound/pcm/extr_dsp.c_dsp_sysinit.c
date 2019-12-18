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
 int /*<<< orphan*/ * EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PCMMAXCHAN ; 
 int /*<<< orphan*/  PCMMAXUNIT ; 
 int /*<<< orphan*/  dev_clone ; 
 int /*<<< orphan*/  dsp_clone ; 
 int /*<<< orphan*/  dsp_cmax ; 
 int /*<<< orphan*/ * dsp_ehtag ; 
 int /*<<< orphan*/  dsp_umax ; 
 int /*<<< orphan*/  snd_unit_init () ; 

__attribute__((used)) static void
dsp_sysinit(void *p)
{
	if (dsp_ehtag != NULL)
		return;
	/* initialize unit numbering */
	snd_unit_init();
	dsp_umax = PCMMAXUNIT;
	dsp_cmax = PCMMAXCHAN;
	dsp_ehtag = EVENTHANDLER_REGISTER(dev_clone, dsp_clone, 0, 1000);
}