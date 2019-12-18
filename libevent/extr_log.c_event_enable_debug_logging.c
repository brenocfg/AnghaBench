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
typedef  int /*<<< orphan*/  ev_uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  event_debug_logging_mask_ ; 

void
event_enable_debug_logging(ev_uint32_t which)
{
#ifdef EVENT_DEBUG_LOGGING_ENABLED
	event_debug_logging_mask_ = which;
#endif
}