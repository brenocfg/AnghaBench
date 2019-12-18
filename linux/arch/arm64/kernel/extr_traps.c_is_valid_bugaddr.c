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

int is_valid_bugaddr(unsigned long addr)
{
	/*
	 * bug_handler() only called for BRK #BUG_BRK_IMM.
	 * So the answer is trivial -- any spurious instances with no
	 * bug table entry will be rejected by report_bug() and passed
	 * back to the debug-monitors code and handled as a fatal
	 * unexpected debug exception.
	 */
	return 1;
}