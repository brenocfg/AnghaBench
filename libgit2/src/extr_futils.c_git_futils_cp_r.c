#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  mode_t ;
typedef  int /*<<< orphan*/  info ;
struct TYPE_10__ {int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ git_buf ;
struct TYPE_11__ {char const* to_root; int flags; int mkdir_flags; TYPE_1__ to; int /*<<< orphan*/  from_prefix; int /*<<< orphan*/  dirmode; } ;
typedef  TYPE_2__ cp_r_info ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int GIT_CPDIR_CHMOD_DIRS ; 
 int GIT_CPDIR_CREATE_EMPTY_DIRS ; 
 int GIT_MKDIR_CHMOD ; 
 int GIT_MKDIR_CHMOD_PATH ; 
 int GIT_MKDIR_PATH ; 
 int GIT_MKDIR_SKIP_LAST ; 
 int _cp_r_callback (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_init (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ git_buf_joinpath (TYPE_1__*,char const*,char*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

int git_futils_cp_r(
	const char *from,
	const char *to,
	uint32_t flags,
	mode_t dirmode)
{
	int error;
	git_buf path = GIT_BUF_INIT;
	cp_r_info info;

	if (git_buf_joinpath(&path, from, "") < 0) /* ensure trailing slash */
		return -1;

	memset(&info, 0, sizeof(info));
	info.to_root = to;
	info.flags   = flags;
	info.dirmode = dirmode;
	info.from_prefix = path.size;
	git_buf_init(&info.to, 0);

	/* precalculate mkdir flags */
	if ((flags & GIT_CPDIR_CREATE_EMPTY_DIRS) == 0) {
		/* if not creating empty dirs, then use mkdir to create the path on
		 * demand right before files are copied.
		 */
		info.mkdir_flags = GIT_MKDIR_PATH | GIT_MKDIR_SKIP_LAST;
		if ((flags & GIT_CPDIR_CHMOD_DIRS) != 0)
			info.mkdir_flags |= GIT_MKDIR_CHMOD_PATH;
	} else {
		/* otherwise, we will do simple mkdir as directories are encountered */
		info.mkdir_flags =
			((flags & GIT_CPDIR_CHMOD_DIRS) != 0) ? GIT_MKDIR_CHMOD : 0;
	}

	error = _cp_r_callback(&info, &path);

	git_buf_dispose(&path);
	git_buf_dispose(&info.to);

	return error;
}