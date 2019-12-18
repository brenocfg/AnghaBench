#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ size; int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;
struct TYPE_8__ {int init_sysdir; TYPE_1__ sysdir; } ;
typedef  TYPE_2__ git_attr_session ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ATTR_FILE_SYSTEM ; 
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  git_buf_attach_notowned (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int git_sysdir_find_system_file (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int system_attr_file(
	git_buf *out,
	git_attr_session *attr_session)
{
	int error;

	if (!attr_session) {
		error = git_sysdir_find_system_file(out, GIT_ATTR_FILE_SYSTEM);

		if (error == GIT_ENOTFOUND)
			git_error_clear();

		return error;
	}

	if (!attr_session->init_sysdir) {
		error = git_sysdir_find_system_file(&attr_session->sysdir, GIT_ATTR_FILE_SYSTEM);

		if (error == GIT_ENOTFOUND)
			git_error_clear();
		else if (error)
			return error;

		attr_session->init_sysdir = 1;
	}

	if (attr_session->sysdir.size == 0)
		return GIT_ENOTFOUND;

	/* We can safely provide a git_buf with no allocation (asize == 0) to
	 * a consumer. This allows them to treat this as a regular `git_buf`,
	 * but their call to `git_buf_dispose` will not attempt to free it.
	 */
	git_buf_attach_notowned(
		out, attr_session->sysdir.ptr, attr_session->sysdir.size);
	return 0;
}