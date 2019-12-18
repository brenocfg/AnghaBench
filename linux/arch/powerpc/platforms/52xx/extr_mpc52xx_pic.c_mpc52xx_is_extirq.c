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

__attribute__((used)) static int mpc52xx_is_extirq(int l1, int l2)
{
	return ((l1 == 0) && (l2 == 0)) ||
	       ((l1 == 1) && (l2 >= 1) && (l2 <= 3));
}