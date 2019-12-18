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
 int /*<<< orphan*/  arg_args_raw ; 
 int /*<<< orphan*/  assert_d_eq (int,int /*<<< orphan*/ ,char*) ; 
 int memcmp (uintptr_t*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
assert_args_raw(uintptr_t *args_raw_expected, int nargs) {
	int cmp = memcmp(args_raw_expected, arg_args_raw,
	    sizeof(uintptr_t) * nargs);
	assert_d_eq(cmp, 0, "Raw args mismatch");
}