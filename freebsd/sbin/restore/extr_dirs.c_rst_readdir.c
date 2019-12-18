#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct direct {scalar_t__ d_reclen; scalar_t__ d_ino; int /*<<< orphan*/  d_name; } ;
struct TYPE_3__ {scalar_t__ dd_loc; scalar_t__ dd_size; scalar_t__ dd_buf; int /*<<< orphan*/  dd_fd; } ;
typedef  TYPE_1__ RST_DIR ;

/* Variables and functions */
 scalar_t__ DIRBLKSIZ ; 
 int /*<<< orphan*/  dprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ maxino ; 
 scalar_t__ read (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

struct direct *
rst_readdir(RST_DIR *dirp)
{
	struct direct *dp;

	for (;;) {
		if (dirp->dd_loc == 0) {
			dirp->dd_size = read(dirp->dd_fd, dirp->dd_buf,
			    DIRBLKSIZ);
			if (dirp->dd_size <= 0) {
				dprintf(stderr, "error reading directory\n");
				return (NULL);
			}
		}
		if (dirp->dd_loc >= dirp->dd_size) {
			dirp->dd_loc = 0;
			continue;
		}
		dp = (struct direct *)(dirp->dd_buf + dirp->dd_loc);
		if (dp->d_reclen == 0 ||
		    dp->d_reclen > DIRBLKSIZ + 1 - dirp->dd_loc) {
			dprintf(stderr, "corrupted directory: bad reclen %d\n",
				dp->d_reclen);
			return (NULL);
		}
		dirp->dd_loc += dp->d_reclen;
		if (dp->d_ino == 0 && strcmp(dp->d_name, "/") == 0)
			return (NULL);
		if (dp->d_ino >= maxino) {
			dprintf(stderr, "corrupted directory: bad inum %d\n",
				dp->d_ino);
			continue;
		}
		return (dp);
	}
}