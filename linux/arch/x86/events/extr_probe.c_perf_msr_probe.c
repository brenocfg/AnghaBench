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
typedef  int /*<<< orphan*/  u64 ;
struct perf_msr {int /*<<< orphan*/  msr; int /*<<< orphan*/  (* test ) (unsigned int,void*) ;struct attribute_group* grp; int /*<<< orphan*/  no_check; } ;
struct attribute_group {int /*<<< orphan*/ * is_visible; } ;

/* Variables and functions */
 unsigned long BIT (unsigned int) ; 
 int BITS_PER_LONG ; 
 int /*<<< orphan*/ * not_visible ; 
 scalar_t__ rdmsrl_safe (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (unsigned int,void*) ; 

unsigned long
perf_msr_probe(struct perf_msr *msr, int cnt, bool zero, void *data)
{
	unsigned long avail = 0;
	unsigned int bit;
	u64 val;

	if (cnt >= BITS_PER_LONG)
		return 0;

	for (bit = 0; bit < cnt; bit++) {
		if (!msr[bit].no_check) {
			struct attribute_group *grp = msr[bit].grp;

			grp->is_visible = not_visible;

			if (msr[bit].test && !msr[bit].test(bit, data))
				continue;
			/* Virt sucks; you cannot tell if a R/O MSR is present :/ */
			if (rdmsrl_safe(msr[bit].msr, &val))
				continue;
			/* Disable zero counters if requested. */
			if (!zero && !val)
				continue;

			grp->is_visible = NULL;
		}
		avail |= BIT(bit);
	}

	return avail;
}