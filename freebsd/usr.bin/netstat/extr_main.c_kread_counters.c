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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  u_long ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ kread (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  kvm_counter_u64_fetch (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmd ; 
 scalar_t__ kvmd_init () ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int /*<<< orphan*/  xo_err (int,char*) ; 
 int /*<<< orphan*/  xo_warnx (char*) ; 

int
kread_counters(u_long addr, void *buf, size_t size)
{
	uint64_t *c;
	u_long *counters;
	size_t i, n;

	if (kvmd_init() < 0)
		return (-1);

	if (size % sizeof(uint64_t) != 0) {
		xo_warnx("kread_counters: invalid counter set size");
		return (-1);
	}

	n = size / sizeof(uint64_t);
	if ((counters = malloc(n * sizeof(u_long))) == NULL)
		xo_err(-1, "malloc");
	if (kread(addr, counters, n * sizeof(u_long)) < 0) {
		free(counters);
		return (-1);
	}

	c = buf;
	for (i = 0; i < n; i++)
		c[i] = kvm_counter_u64_fetch(kvmd, counters[i]);

	free(counters);
	return (0);
}