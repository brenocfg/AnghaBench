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
struct dirent {scalar_t__ d_fileno; int /*<<< orphan*/  d_name; scalar_t__ d_namlen; } ;
struct direct {scalar_t__ d_ino; scalar_t__ d_namlen; int /*<<< orphan*/  d_name; } ;

/* Variables and functions */
 scalar_t__ TSTINO (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ UFS_WINO ; 
 scalar_t__ dflag ; 
 int /*<<< orphan*/  dumpmap ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 struct direct* rst_readdir (void*) ; 
 int /*<<< orphan*/  vflag ; 

struct dirent *
glob_readdir(void *dirp)
{
	struct direct *dp;
	static struct dirent adirent;

	while ((dp = rst_readdir(dirp)) != NULL) {
		if (!vflag && dp->d_ino == UFS_WINO)
			continue;
		if (dflag || TSTINO(dp->d_ino, dumpmap))
			break;
	}
	if (dp == NULL)
		return (NULL);
	adirent.d_fileno = dp->d_ino;
	adirent.d_namlen = dp->d_namlen;
	memmove(adirent.d_name, dp->d_name, dp->d_namlen + 1);
	return (&adirent);
}