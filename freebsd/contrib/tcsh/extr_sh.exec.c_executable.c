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
typedef  scalar_t__ const Char ;

/* Variables and functions */
 scalar_t__ S_ISDIR (int) ; 
 scalar_t__ S_ISREG (int) ; 
 int S_IXGRP ; 
 int S_IXOTH ; 
 int S_IXUSR ; 
 scalar_t__ const* Strspl (scalar_t__ const*,scalar_t__ const*) ; 
 int /*<<< orphan*/  X_OK ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 char* short2str (scalar_t__ const*) ; 
 int stat (char*,struct stat*) ; 
 int /*<<< orphan*/  xfree (scalar_t__ const*) ; 

int
executable(const Char *dir, const Char *name, int dir_ok)
{
    struct stat stbuf;
    char   *strname;

    if (dir && *dir) {
	Char *path;

	path = Strspl(dir, name);
	strname = short2str(path);
	xfree(path);
    }
    else
	strname = short2str(name);

    return (stat(strname, &stbuf) != -1 &&
	    ((dir_ok && S_ISDIR(stbuf.st_mode)) ||
	     (S_ISREG(stbuf.st_mode) &&
    /* save time by not calling access() in the hopeless case */
	      (stbuf.st_mode & (S_IXOTH | S_IXGRP | S_IXUSR)) &&
	      access(strname, X_OK) == 0
	)));
}