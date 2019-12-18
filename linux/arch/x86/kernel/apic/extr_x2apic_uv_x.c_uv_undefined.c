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
 int /*<<< orphan*/  disable_uv_undefined_panic ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  panic (char*,char*) ; 
 int /*<<< orphan*/  pr_crit (char*,char*) ; 

unsigned long uv_undefined(char *str)
{
	if (likely(!disable_uv_undefined_panic))
		panic("UV: error: undefined MMR: %s\n", str);
	else
		pr_crit("UV: error: undefined MMR: %s\n", str);

	/* Cause a machine fault: */
	return ~0ul;
}