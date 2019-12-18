#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;
struct TYPE_7__ {int* ptr; size_t size; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_OBJECT_COMMIT ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_joinpath (TYPE_1__*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_futils_readbuffer (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  git_futils_writebuffer (TYPE_1__*,int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_repository_path (int /*<<< orphan*/ ) ; 

void test_object_lookup__lookup_corrupt_object_returns_error(void)
{
	const char *commit = "8e73b769e97678d684b809b163bebdae2911720f",
	      *file = "objects/8e/73b769e97678d684b809b163bebdae2911720f";
	git_buf path = GIT_BUF_INIT, contents = GIT_BUF_INIT;
	git_oid oid;
	git_object *object;
	size_t i;

	cl_git_pass(git_oid_fromstr(&oid, commit));
	cl_git_pass(git_buf_joinpath(&path, git_repository_path(g_repo), file));
	cl_git_pass(git_futils_readbuffer(&contents, path.ptr));

	/* Corrupt and try to read the object */
	for (i = 0; i < contents.size; i++) {
		contents.ptr[i] ^= 0x1;
		cl_git_pass(git_futils_writebuffer(&contents, path.ptr, O_RDWR, 0644));
		cl_git_fail(git_object_lookup(&object, g_repo, &oid, GIT_OBJECT_COMMIT));
		contents.ptr[i] ^= 0x1;
	}

	/* Restore original content and assert we can read the object */
	cl_git_pass(git_futils_writebuffer(&contents, path.ptr, O_RDWR, 0644));
	cl_git_pass(git_object_lookup(&object, g_repo, &oid, GIT_OBJECT_COMMIT));

	git_object_free(object);
	git_buf_dispose(&path);
	git_buf_dispose(&contents);
}