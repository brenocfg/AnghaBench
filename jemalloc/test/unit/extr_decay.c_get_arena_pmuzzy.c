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
typedef  int /*<<< orphan*/  pmuzzy ;
typedef  int /*<<< orphan*/  mib ;

/* Variables and functions */
 int /*<<< orphan*/  assert_d_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  do_epoch () ; 
 int /*<<< orphan*/  mallctlbymib (size_t*,size_t,void*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mallctlnametomib (char*,size_t*,size_t*) ; 

__attribute__((used)) static size_t
get_arena_pmuzzy(unsigned arena_ind) {
	do_epoch();
	size_t mib[4];
	size_t miblen = sizeof(mib)/sizeof(size_t);
	assert_d_eq(mallctlnametomib("stats.arenas.0.pmuzzy", mib, &miblen), 0,
	    "Unexpected mallctlnametomib() failure");
	mib[2] = (size_t)arena_ind;
	size_t pmuzzy;
	size_t sz = sizeof(pmuzzy);
	assert_d_eq(mallctlbymib(mib, miblen, (void *)&pmuzzy, &sz, NULL, 0), 0,
	    "Unexpected mallctlbymib() failure");
	return pmuzzy;
}