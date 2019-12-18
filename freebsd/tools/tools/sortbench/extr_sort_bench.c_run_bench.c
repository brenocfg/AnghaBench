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
typedef  enum test { ____Placeholder_test } test ;
typedef  enum sort { ____Placeholder_sort } sort ;

/* Variables and functions */
 int /*<<< orphan*/  EX_DATAERR ; 
#define  INVALID_TEST 132 
#define  PART 131 
#define  RAND 130 
#define  REV 129 
#define  SORT 128 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  partial_bench (int,int) ; 
 int /*<<< orphan*/  rand_bench (int,int) ; 
 int /*<<< orphan*/  reverse_bench (int,int) ; 
 int /*<<< orphan*/  sort_bench (int,int) ; 

__attribute__((used)) static void
run_bench(enum sort s, enum test t, int runs, int elts)
{
	for (int i = 0; i < runs; i++) {
		switch (t) {
		case RAND:
			rand_bench(elts, s);
			break;
		case SORT:
			sort_bench(elts, s);
			break;
		case PART:
			partial_bench(elts, s);
			break;
		case REV:
			reverse_bench(elts, s);
			break;
		// Should never be reached
		case INVALID_TEST:
			exit(EX_DATAERR);
		}
	}
}