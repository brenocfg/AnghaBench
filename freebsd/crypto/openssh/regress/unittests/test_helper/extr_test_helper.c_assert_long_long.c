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
typedef  enum test_predicate { ____Placeholder_test_predicate } test_predicate ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_CHECK (long long,long long,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,long long,long long) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  test_die () ; 
 int /*<<< orphan*/  test_header (char const*,int,char const*,char const*,char*,int) ; 

void
assert_long_long(const char *file, int line, const char *a1, const char *a2,
    long long aa1, long long aa2, enum test_predicate pred)
{
	TEST_CHECK(aa1, aa2, pred);
	test_header(file, line, a1, a2, "LONG LONG", pred);
	fprintf(stderr, "%12s = %lld / 0x%llx\n", a1, aa1, aa1);
	fprintf(stderr, "%12s = %lld / 0x%llx\n", a2, aa2, aa2);
	test_die();
}