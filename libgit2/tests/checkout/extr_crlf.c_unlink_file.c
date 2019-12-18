#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_UNUSED (void*) ; 
 int /*<<< orphan*/  cl_assert (char*) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git__free (char*) ; 
 char* git_path_basename (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_unlink (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int unlink_file(void *payload, git_buf *path)
{
	char *fn;

	cl_assert(fn = git_path_basename(path->ptr));

	GIT_UNUSED(payload);

	if (strcmp(fn, ".git"))
		cl_must_pass(p_unlink(path->ptr));

	git__free(fn);
	return 0;
}