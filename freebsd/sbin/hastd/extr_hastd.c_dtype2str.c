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
typedef  int /*<<< orphan*/  mode_t ;

/* Variables and functions */
 scalar_t__ S_ISBLK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISFIFO (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISSOCK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISWHT (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
dtype2str(mode_t mode)
{

	if (S_ISBLK(mode))
		return ("block device");
	else if (S_ISCHR(mode))
		return ("character device");
	else if (S_ISDIR(mode))
		return ("directory");
	else if (S_ISFIFO(mode))
		return ("pipe or FIFO");
	else if (S_ISLNK(mode))
		return ("symbolic link");
	else if (S_ISREG(mode))
		return ("regular file");
	else if (S_ISSOCK(mode))
		return ("socket");
	else if (S_ISWHT(mode))
		return ("whiteout");
	else
		return ("unknown");
}