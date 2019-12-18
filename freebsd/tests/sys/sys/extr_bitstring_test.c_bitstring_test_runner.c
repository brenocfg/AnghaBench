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
typedef  int /*<<< orphan*/  testfunc_t ;

/* Variables and functions */
 int _BITSTR_BITS ; 
 int /*<<< orphan*/  bitstring_run_heap_test (int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/  bitstring_run_stack_test (int /*<<< orphan*/ *,int const) ; 
 unsigned long nitems (int const*) ; 

__attribute__((used)) static void
bitstring_test_runner(testfunc_t *test)
{
	const int bitstr_sizes[] = {
		0,
		1,
		_BITSTR_BITS - 1,
		_BITSTR_BITS,
		_BITSTR_BITS + 1,
		2 * _BITSTR_BITS - 1,
		2 * _BITSTR_BITS,
		1023,
		1024
	};

	for (unsigned long i = 0; i < nitems(bitstr_sizes); i++) {
		bitstring_run_stack_test(test, bitstr_sizes[i]);
		bitstring_run_heap_test(test, bitstr_sizes[i]);
	}
}