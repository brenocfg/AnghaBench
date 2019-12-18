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
 int /*<<< orphan*/  MIN (size_t,int) ; 
 int /*<<< orphan*/  TEST_CHECK_INT (int,int) ; 
 int /*<<< orphan*/  TEST_NE ; 
 int /*<<< orphan*/  assert_ptr (char const*,int,char const*,char*,void const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char*,size_t) ; 
 int memcmp (void const*,void const*,size_t) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  test_die () ; 
 int /*<<< orphan*/  test_header (char const*,int,char const*,char const*,char*,int) ; 
 char* tohex (void const*,int /*<<< orphan*/ ) ; 

void
assert_mem(const char *file, int line, const char *a1, const char *a2,
    const void *aa1, const void *aa2, size_t l, enum test_predicate pred)
{
	int r;

	if (l == 0)
		return;
	/* If length is >0, then verify pointers are not NULL */
	assert_ptr(file, line, a1, "NULL", aa1, NULL, TEST_NE);
	assert_ptr(file, line, a2, "NULL", aa2, NULL, TEST_NE);

	r = memcmp(aa1, aa2, l);
	TEST_CHECK_INT(r, pred);
	test_header(file, line, a1, a2, "STRING", pred);
	fprintf(stderr, "%12s = %s (len %zu)\n", a1, tohex(aa1, MIN(l, 256)), l);
	fprintf(stderr, "%12s = %s (len %zu)\n", a2, tohex(aa2, MIN(l, 256)), l);
	test_die();
}