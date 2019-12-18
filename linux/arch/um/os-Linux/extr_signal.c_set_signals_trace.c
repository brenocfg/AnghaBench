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
 int /*<<< orphan*/  block_signals_trace () ; 
 int signals_enabled ; 
 int /*<<< orphan*/  unblock_signals_trace () ; 

int set_signals_trace(int enable)
{
	int ret;
	if (signals_enabled == enable)
		return enable;

	ret = signals_enabled;
	if (enable)
		unblock_signals_trace();
	else
		block_signals_trace();

	return ret;
}