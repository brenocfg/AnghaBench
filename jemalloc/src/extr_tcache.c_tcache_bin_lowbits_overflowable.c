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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 scalar_t__ total_stack_bytes ; 

__attribute__((used)) static bool
tcache_bin_lowbits_overflowable(void *ptr) {
	uint32_t lowbits = (uint32_t)((uintptr_t)ptr + total_stack_bytes);
	return lowbits < (uint32_t)(uintptr_t)ptr;
}