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

/* Variables and functions */
 scalar_t__ LineNo ; 
 int /*<<< orphan*/ * _fs_fp ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ fsp_set ; 
 int /*<<< orphan*/ * getenv (char*) ; 
 scalar_t__ issetugid () ; 
 int /*<<< orphan*/  path_fstab ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setfstab (int /*<<< orphan*/ *) ; 

int
setfsent(void)
{
	if (_fs_fp) {
		rewind(_fs_fp);
		LineNo = 0;
		return (1);
	}
	if (fsp_set == 0) {
		if (issetugid())
			setfstab(NULL);
		else
			setfstab(getenv("PATH_FSTAB"));
	}
	if ((_fs_fp = fopen(path_fstab, "re")) != NULL) {
		LineNo = 0;
		return (1);
	}
	error(errno);
	return (0);
}