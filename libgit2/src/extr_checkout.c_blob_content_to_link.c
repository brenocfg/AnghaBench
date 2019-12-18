#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  git_buf ;
typedef  int /*<<< orphan*/  git_blob ;
struct TYPE_7__ {int /*<<< orphan*/  stat_calls; } ;
struct TYPE_6__ {int /*<<< orphan*/  dir_mode; } ;
struct TYPE_8__ {TYPE_2__ perfdata; scalar_t__ can_symlink; TYPE_1__ opts; } ;
typedef  TYPE_3__ checkout_data ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_ERROR_CHECKOUT ; 
 int /*<<< orphan*/  GIT_ERROR_OS ; 
 int /*<<< orphan*/  GIT_FILEMODE_LINK ; 
 int git_blob__getbuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char const*) ; 
 int git_futils_fake_symlink (int /*<<< orphan*/ ,char const*) ; 
 int mkpath2file (TYPE_3__*,char const*,int /*<<< orphan*/ ) ; 
 int p_lstat (char const*,struct stat*) ; 
 int p_symlink (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int blob_content_to_link(
	checkout_data *data,
	struct stat *st,
	git_blob *blob,
	const char *path)
{
	git_buf linktarget = GIT_BUF_INIT;
	int error;

	if ((error = mkpath2file(data, path, data->opts.dir_mode)) < 0)
		return error;

	if ((error = git_blob__getbuf(&linktarget, blob)) < 0)
		return error;

	if (data->can_symlink) {
		if ((error = p_symlink(git_buf_cstr(&linktarget), path)) < 0)
			git_error_set(GIT_ERROR_OS, "could not create symlink %s", path);
	} else {
		error = git_futils_fake_symlink(git_buf_cstr(&linktarget), path);
	}

	if (!error) {
		data->perfdata.stat_calls++;

		if ((error = p_lstat(path, st)) < 0)
			git_error_set(GIT_ERROR_CHECKOUT, "could not stat symlink %s", path);

		st->st_mode = GIT_FILEMODE_LINK;
	}

	git_buf_dispose(&linktarget);

	return error;
}