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
struct inotab {int /*<<< orphan*/  t_seekpt; } ;
struct direct {int d_namlen; int /*<<< orphan*/  d_name; } ;
typedef  int /*<<< orphan*/  ino_t ;

/* Variables and functions */
 int /*<<< orphan*/  dirp ; 
 struct inotab* inotablookup (int /*<<< orphan*/ ) ; 
 struct direct* rst_readdir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rst_seekdir (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static struct direct *
searchdir(ino_t	inum, char *name)
{
	struct direct *dp;
	struct inotab *itp;
	int len;

	itp = inotablookup(inum);
	if (itp == NULL)
		return (NULL);
	rst_seekdir(dirp, itp->t_seekpt, itp->t_seekpt);
	len = strlen(name);
	do {
		dp = rst_readdir(dirp);
		if (dp == NULL)
			return (NULL);
	} while (dp->d_namlen != len || strncmp(dp->d_name, name, len) != 0);
	return (dp);
}