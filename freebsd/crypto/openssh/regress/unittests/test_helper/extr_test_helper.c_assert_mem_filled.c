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
typedef  int u_char ;
typedef  int /*<<< orphan*/  tmp ;
typedef  enum test_predicate { ____Placeholder_test_predicate } test_predicate ;

/* Variables and functions */
 int /*<<< orphan*/  MIN (size_t,int) ; 
 int /*<<< orphan*/  TEST_CHECK_INT (int,int) ; 
 int /*<<< orphan*/  TEST_NE ; 
 int /*<<< orphan*/  assert_ptr (char const*,int,char const*,char*,void const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int memvalcmp (void const*,int,size_t,size_t*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,size_t) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  test_die () ; 
 int /*<<< orphan*/  test_header (char const*,int,char const*,int /*<<< orphan*/ *,char*,int) ; 
 char* tohex (void const*,int /*<<< orphan*/ ) ; 

void
assert_mem_filled(const char *file, int line, const char *a1,
    const void *aa1, u_char v, size_t l, enum test_predicate pred)
{
	size_t where = -1;
	int r;
	char tmp[64];

	if (l == 0)
		return;
	/* If length is >0, then verify the pointer is not NULL */
	assert_ptr(file, line, a1, "NULL", aa1, NULL, TEST_NE);

	r = memvalcmp(aa1, v, l, &where);
	TEST_CHECK_INT(r, pred);
	test_header(file, line, a1, NULL, "MEM_ZERO", pred);
	fprintf(stderr, "%20s = %s%s (len %zu)\n", a1,
	    tohex(aa1, MIN(l, 20)), l > 20 ? "..." : "", l);
	snprintf(tmp, sizeof(tmp), "(%s)[%zu]", a1, where);
	fprintf(stderr, "%20s = 0x%02x (expected 0x%02x)\n", tmp,
	    ((u_char *)aa1)[where], v);
	test_die();
}