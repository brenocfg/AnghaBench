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
struct stat {int /*<<< orphan*/  st_mode; } ;
struct direct {scalar_t__ d_ino; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFDIR ; 
 int /*<<< orphan*/  IFREG ; 
 scalar_t__ NODE ; 
 scalar_t__ TSTINO (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ UFS_WINO ; 
 int /*<<< orphan*/  dflag ; 
 int /*<<< orphan*/  dumpmap ; 
 scalar_t__ inodetype (scalar_t__) ; 
 struct direct* pathsearch (char const*) ; 
 int /*<<< orphan*/  vflag ; 

__attribute__((used)) static int
glob_stat(const char *name, struct stat *stp)
{
	struct direct *dp;

	dp = pathsearch(name);
	if (dp == NULL || (!dflag && TSTINO(dp->d_ino, dumpmap) == 0) ||
	    (!vflag && dp->d_ino == UFS_WINO))
		return (-1);
	if (inodetype(dp->d_ino) == NODE)
		stp->st_mode = IFDIR;
	else
		stp->st_mode = IFREG;
	return (0);
}