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
 scalar_t__ ARM_DEBUG_ARCH_V8 ; 
 scalar_t__ get_debug_arch () ; 

__attribute__((used)) static int debug_exception_updates_fsr(void)
{
	return get_debug_arch() >= ARM_DEBUG_ARCH_V8;
}