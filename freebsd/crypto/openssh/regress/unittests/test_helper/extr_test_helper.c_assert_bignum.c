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
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 char* BN_bn2hex (int /*<<< orphan*/  const*) ; 
 int BN_cmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  TEST_CHECK_INT (int,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  test_die () ; 
 int /*<<< orphan*/  test_header (char const*,int,char const*,char const*,char*,int) ; 

void
assert_bignum(const char *file, int line, const char *a1, const char *a2,
    const BIGNUM *aa1, const BIGNUM *aa2, enum test_predicate pred)
{
	int r = BN_cmp(aa1, aa2);

	TEST_CHECK_INT(r, pred);
	test_header(file, line, a1, a2, "BIGNUM", pred);
	fprintf(stderr, "%12s = 0x%s\n", a1, BN_bn2hex(aa1));
	fprintf(stderr, "%12s = 0x%s\n", a2, BN_bn2hex(aa2));
	test_die();
}