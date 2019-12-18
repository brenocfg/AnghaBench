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
 int /*<<< orphan*/  printf (char*,char const*,char const*,int,int) ; 

int
ipdn_bound_var(int *v, int dflt, int lo, int hi, const char *msg)
{
	int oldv = *v;
	const char *op = NULL;
	if (dflt < lo)
		dflt = lo;
	if (dflt > hi)
		dflt = hi;
	if (oldv < lo) {
		*v = dflt;
		op = "Bump";
	} else if (oldv > hi) {
		*v = hi;
		op = "Clamp";
	} else
		return *v;
	if (op && msg)
		printf("%s %s to %d (was %d)\n", op, msg, *v, oldv);
	return *v;
}