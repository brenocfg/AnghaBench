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
typedef  int /*<<< orphan*/  mib ;

/* Variables and functions */
 int /*<<< orphan*/  assert_d_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  mallctlbymib (size_t*,size_t,void*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mallctlnametomib (char const*,size_t*,size_t*) ; 

__attribute__((used)) static size_t
do_get_size_impl(const char *cmd, unsigned arena_ind) {
	size_t mib[4];
	size_t miblen = sizeof(mib) / sizeof(size_t);
	size_t z = sizeof(size_t);

	assert_d_eq(mallctlnametomib(cmd, mib, &miblen),
	    0, "Unexpected mallctlnametomib(\"%s\", ...) failure", cmd);
	mib[2] = arena_ind;
	size_t size;
	assert_d_eq(mallctlbymib(mib, miblen, (void *)&size, &z, NULL, 0),
	    0, "Unexpected mallctlbymib([\"%s\"], ...) failure", cmd);

	return size;
}