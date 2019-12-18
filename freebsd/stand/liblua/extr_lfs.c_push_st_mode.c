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
struct stat {int st_mode; } ;
typedef  int mode_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int S_IFMT ; 
 scalar_t__ S_ISBLK (int) ; 
 scalar_t__ S_ISCHR (int) ; 
 scalar_t__ S_ISDIR (int) ; 
 scalar_t__ S_ISFIFO (int) ; 
 scalar_t__ S_ISLNK (int) ; 
 scalar_t__ S_ISREG (int) ; 
 scalar_t__ S_ISSOCK (int) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static void
push_st_mode(lua_State *L, struct stat *sb)
{
	const char *mode_s;
	mode_t mode;

	mode = (sb->st_mode & S_IFMT);
	if (S_ISREG(mode))
		mode_s = "file";
	else if (S_ISDIR(mode))
		mode_s = "directory";
	else if (S_ISLNK(mode))
		mode_s = "link";
	else if (S_ISSOCK(mode))
		mode_s = "socket";
	else if (S_ISFIFO(mode))
		mode_s = "fifo";
	else if (S_ISCHR(mode))
		mode_s = "char device";
	else if (S_ISBLK(mode))
		mode_s = "block device";
	else
		mode_s = "other";

	lua_pushstring(L, mode_s);
}