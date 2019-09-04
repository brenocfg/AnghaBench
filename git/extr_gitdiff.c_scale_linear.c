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

__attribute__((used)) static int scale_linear(int it, int width, int max_change)
{
	if (!it)
		return 0;
	/*
	 * make sure that at least one '-' or '+' is printed if
	 * there is any change to this path. The easiest way is to
	 * scale linearly as if the alloted width is one column shorter
	 * than it is, and then add 1 to the result.
	 */
	return 1 + (it * (width - 1) / max_change);
}