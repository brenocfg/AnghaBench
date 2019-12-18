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

const char *
inode_type(mode_t mode)
{
	if (S_ISREG(mode))
		return ("file");
	if (S_ISLNK(mode))
		return ("symlink");
	if (S_ISDIR(mode))
		return ("dir");
	if (S_ISLNK(mode))
		return ("link");
	if (S_ISFIFO(mode))
		return ("fifo");
	if (S_ISSOCK(mode))
		return ("socket");
	/* XXX should not happen but handle them */
	if (S_ISCHR(mode))
		return ("char");
	if (S_ISBLK(mode))
		return ("block");
	return ("unknown");
}