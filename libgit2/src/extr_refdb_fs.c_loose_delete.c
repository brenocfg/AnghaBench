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
struct TYPE_7__ {int /*<<< orphan*/  commonpath; } ;
typedef  TYPE_1__ refdb_fs_backend ;
struct TYPE_8__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_2__ git_buf ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 TYPE_2__ GIT_BUF_INIT ; 
 int GIT_ENOTFOUND ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_2__*) ; 
 scalar_t__ git_buf_joinpath (TYPE_2__*,int /*<<< orphan*/ ,char const*) ; 
 int p_unlink (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int loose_delete(refdb_fs_backend *backend, const char *ref_name)
{
	git_buf loose_path = GIT_BUF_INIT;
	int error = 0;

	if (git_buf_joinpath(&loose_path, backend->commonpath, ref_name) < 0)
		return -1;

	error = p_unlink(loose_path.ptr);
	if (error < 0 && errno == ENOENT)
		error = GIT_ENOTFOUND;
	else if (error != 0)
		error = -1;

	git_buf_dispose(&loose_path);

	return error;
}