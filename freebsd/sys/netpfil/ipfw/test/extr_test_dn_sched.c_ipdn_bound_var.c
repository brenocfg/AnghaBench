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

int
ipdn_bound_var(int *v, int dflt, int lo, int hi, const char *msg)
{
	(void)msg;
        if (*v < lo) {
                *v = dflt;
        } else if (*v > hi) {
                *v = hi;
        }
        return *v;
}