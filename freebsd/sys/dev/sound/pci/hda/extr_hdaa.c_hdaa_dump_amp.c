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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  HDA_PARAM_OUTPUT_AMP_CAP_MUTE_CAP (int /*<<< orphan*/ ) ; 
 int HDA_PARAM_OUTPUT_AMP_CAP_NUMSTEPS (int /*<<< orphan*/ ) ; 
 int HDA_PARAM_OUTPUT_AMP_CAP_OFFSET (int /*<<< orphan*/ ) ; 
 int HDA_PARAM_OUTPUT_AMP_CAP_STEPSIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int) ; 

__attribute__((used)) static void
hdaa_dump_amp(device_t dev, uint32_t cap, const char *banner)
{
	int offset, size, step;

	offset = HDA_PARAM_OUTPUT_AMP_CAP_OFFSET(cap);
	size = HDA_PARAM_OUTPUT_AMP_CAP_STEPSIZE(cap);
	step = HDA_PARAM_OUTPUT_AMP_CAP_NUMSTEPS(cap);
	device_printf(dev, "     %s amp: 0x%08x "
	    "mute=%d step=%d size=%d offset=%d (%+d/%+ddB)\n",
	    banner, cap,
	    HDA_PARAM_OUTPUT_AMP_CAP_MUTE_CAP(cap),
	    step, size, offset,
	    ((0 - offset) * (size + 1)) / 4,
	    ((step - offset) * (size + 1)) / 4);
}