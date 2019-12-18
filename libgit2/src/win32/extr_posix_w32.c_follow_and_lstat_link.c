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
struct stat {int dummy; } ;
typedef  int /*<<< orphan*/  git_win32_path ;

/* Variables and functions */
 scalar_t__ getfinalpath_w (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lstat_w (int /*<<< orphan*/ ,struct stat*,int) ; 

__attribute__((used)) static int follow_and_lstat_link(git_win32_path path, struct stat* buf)
{
	git_win32_path target_w;

	if (getfinalpath_w(target_w, path) < 0)
		return -1;

	return lstat_w(target_w, buf, false);
}