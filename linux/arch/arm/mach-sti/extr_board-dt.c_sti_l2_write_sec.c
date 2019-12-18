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

__attribute__((used)) static void sti_l2_write_sec(unsigned long val, unsigned reg)
{
	/*
	 * We can't write to secure registers as we are in non-secure
	 * mode, until we have some SMI service available.
	 */
}