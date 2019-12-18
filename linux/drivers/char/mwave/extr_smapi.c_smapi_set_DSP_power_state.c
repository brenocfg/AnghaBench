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
 int EIO ; 
 int /*<<< orphan*/  PRINTK_2 (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  TRACE_SMAPI ; 
 int smapi_request (int,int,int /*<<< orphan*/ ,unsigned short,unsigned short*,unsigned short*,unsigned short*,unsigned short*,unsigned short*,unsigned short*) ; 

int smapi_set_DSP_power_state(bool bOn)
{
	int bRC = -EIO;
	unsigned short usAX, usBX, usCX, usDX, usDI, usSI;
	unsigned short usPowerFunction;

	PRINTK_2(TRACE_SMAPI, "smapi::smapi_set_DSP_power_state entry bOn %x\n", bOn);

	usPowerFunction = (bOn) ? 1 : 0;

	bRC = smapi_request(0x4901, 0x0000, 0, usPowerFunction,
		&usAX, &usBX, &usCX, &usDX, &usDI, &usSI);

	PRINTK_2(TRACE_SMAPI, "smapi::smapi_set_DSP_power_state exit bRC %x\n", bRC);

	return bRC;
}