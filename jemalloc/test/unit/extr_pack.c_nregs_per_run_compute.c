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
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  nregs ;
typedef  int /*<<< orphan*/  mib ;

/* Variables and functions */
 int /*<<< orphan*/  assert_d_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 unsigned int binind_compute () ; 
 int /*<<< orphan*/  mallctlbymib (size_t*,size_t,void*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mallctlnametomib (char*,size_t*,size_t*) ; 

__attribute__((used)) static size_t
nregs_per_run_compute(void) {
	uint32_t nregs;
	size_t sz;
	unsigned binind = binind_compute();
	size_t mib[4];
	size_t miblen = sizeof(mib)/sizeof(size_t);

	assert_d_eq(mallctlnametomib("arenas.bin.0.nregs", mib, &miblen), 0,
	    "Unexpected mallctlnametomb failure");
	mib[2] = (size_t)binind;
	sz = sizeof(nregs);
	assert_d_eq(mallctlbymib(mib, miblen, (void *)&nregs, &sz, NULL,
	    0), 0, "Unexpected mallctlbymib failure");
	return nregs;
}