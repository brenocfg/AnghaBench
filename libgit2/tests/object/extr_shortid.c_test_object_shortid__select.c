#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;
struct TYPE_4__ {int /*<<< orphan*/  ptr; int /*<<< orphan*/  size; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_OBJECT_ANY ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_object_short_id (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 

void test_object_shortid__select(void)
{
	git_oid full;
	git_object *obj;
	git_buf shorty = {0};

	git_oid_fromstr(&full, "ce013625030ba8dba906f756967f9e9ca394464a");
	cl_git_pass(git_object_lookup(&obj, _repo, &full, GIT_OBJECT_ANY));
	cl_git_pass(git_object_short_id(&shorty, obj));
	cl_assert_equal_i(7, shorty.size);
	cl_assert_equal_s("ce01362", shorty.ptr);
	git_object_free(obj);

	git_oid_fromstr(&full, "038d718da6a1ebbc6a7780a96ed75a70cc2ad6e2");
	cl_git_pass(git_object_lookup(&obj, _repo, &full, GIT_OBJECT_ANY));
	cl_git_pass(git_object_short_id(&shorty, obj));
	cl_assert_equal_i(7, shorty.size);
	cl_assert_equal_s("038d718", shorty.ptr);
	git_object_free(obj);

	git_oid_fromstr(&full, "dea509d097ce692e167dfc6a48a7a280cc5e877e");
	cl_git_pass(git_object_lookup(&obj, _repo, &full, GIT_OBJECT_ANY));
	cl_git_pass(git_object_short_id(&shorty, obj));
	cl_assert_equal_i(9, shorty.size);
	cl_assert_equal_s("dea509d09", shorty.ptr);
	git_object_free(obj);

	git_oid_fromstr(&full, "dea509d0b3cb8ee0650f6ca210bc83f4678851ba");
	cl_git_pass(git_object_lookup(&obj, _repo, &full, GIT_OBJECT_ANY));
	cl_git_pass(git_object_short_id(&shorty, obj));
	cl_assert_equal_i(9, shorty.size);
	cl_assert_equal_s("dea509d0b", shorty.ptr);
	git_object_free(obj);

	git_buf_dispose(&shorty);
}