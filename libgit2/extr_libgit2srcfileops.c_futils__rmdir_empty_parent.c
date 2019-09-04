#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ baselen; int flags; } ;
typedef  TYPE_1__ futils__rmdir_data ;

/* Variables and functions */
 int EBUSY ; 
 int EEXIST ; 
 int ENOENT ; 
 int ENOTDIR ; 
 int ENOTEMPTY ; 
 int GIT_ITEROVER ; 
 int GIT_RMDIR_SKIP_NONEMPTY ; 
 int errno ; 
 int git_path_set_error (int,char const*,char*) ; 
 scalar_t__ p_rmdir (char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static int futils__rmdir_empty_parent(void *opaque, const char *path)
{
	futils__rmdir_data *data = opaque;
	int error = 0;

	if (strlen(path) <= data->baselen)
		error = GIT_ITEROVER;

	else if (p_rmdir(path) < 0) {
		int en = errno;

		if (en == ENOENT || en == ENOTDIR) {
			/* do nothing */
		} else if ((data->flags & GIT_RMDIR_SKIP_NONEMPTY) == 0 &&
			en == EBUSY) {
			error = git_path_set_error(errno, path, "rmdir");
		} else if (en == ENOTEMPTY || en == EEXIST || en == EBUSY) {
			error = GIT_ITEROVER;
		} else {
			error = git_path_set_error(errno, path, "rmdir");
		}
	}

	return error;
}