#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  oid_hex ;
struct TYPE_6__ {int page_size; } ;
typedef  TYPE_1__ git_pool ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int GIT_OID_HEXSZ ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_pool__open_pages (TYPE_1__*) ; 
 int /*<<< orphan*/  git_pool_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  git_pool_init (TYPE_1__*,int) ; 
 int /*<<< orphan*/ * git_pool_malloc (TYPE_1__*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 char* to_hex ; 

void test_core_pool__2(void)
{
	git_pool p;
	char oid_hex[GIT_OID_HEXSZ];
	git_oid *oid;
	int i, j;

	memset(oid_hex, '0', sizeof(oid_hex));

	git_pool_init(&p, sizeof(git_oid));
	p.page_size = 4000;

	for (i = 1000; i < 10000; i++) {
		oid = git_pool_malloc(&p, 1);
		cl_assert(oid != NULL);

		for (j = 0; j < 8; j++)
			oid_hex[j] = to_hex[(i >> (4 * j)) & 0x0f];
		cl_git_pass(git_oid_fromstr(oid, oid_hex));
	}

#ifndef GIT_DEBUG_POOL
	/* with fixed page size, allocation must end up with these values */
	cl_assert_equal_i(sizeof(void *) == 8 ? 55 : 45, git_pool__open_pages(&p));
#endif
	git_pool_clear(&p);
}