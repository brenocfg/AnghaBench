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
typedef  union dinode {int dummy; } dinode ;
typedef  char* uintmax_t ;
typedef  scalar_t__ ino_t ;

/* Variables and functions */
 int DIP (union dinode*,int /*<<< orphan*/ ) ; 
 int IFDIR ; 
 int IFMT ; 
 int /*<<< orphan*/  MAXPATHLEN ; 
 scalar_t__ UFS_ROOTINO ; 
 int /*<<< orphan*/  di_mode ; 
 scalar_t__ ftypeok (union dinode*) ; 
 int /*<<< orphan*/  getpathname (char*,scalar_t__,scalar_t__) ; 
 union dinode* ginode (scalar_t__) ; 
 scalar_t__ maxino ; 
 int /*<<< orphan*/  pfatal (char*,char*,...) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  prtinode (scalar_t__,union dinode*) ; 
 int /*<<< orphan*/  pwarn (char*,char const*) ; 

void
fileerror(ino_t cwd, ino_t ino, const char *errmesg)
{
	union dinode *dp;
	char pathbuf[MAXPATHLEN + 1];

	pwarn("%s ", errmesg);
	if (ino < UFS_ROOTINO || ino > maxino) {
		pfatal("out-of-range inode number %ju", (uintmax_t)ino);
		return;
	}
	dp = ginode(ino);
	prtinode(ino, dp);
	printf("\n");
	getpathname(pathbuf, cwd, ino);
	if (ftypeok(dp))
		pfatal("%s=%s\n",
		    (DIP(dp, di_mode) & IFMT) == IFDIR ? "DIR" : "FILE",
		    pathbuf);
	else
		pfatal("NAME=%s\n", pathbuf);
}