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
struct direct {int /*<<< orphan*/  d_ino; } ;
typedef  int /*<<< orphan*/  ino_t ;

/* Variables and functions */
 int MAXPATHLEN ; 
 int /*<<< orphan*/  UFS_ROOTINO ; 
 struct direct* searchdir (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 char* strsep (char**,char*) ; 

struct direct *
pathsearch(const char *pathname)
{
	ino_t ino;
	struct direct *dp;
	char *path, *name, buffer[MAXPATHLEN];

	strcpy(buffer, pathname);
	path = buffer;
	ino = UFS_ROOTINO;
	while (*path == '/')
		path++;
	dp = NULL;
	while ((name = strsep(&path, "/")) != NULL && *name != '\0') {
		if ((dp = searchdir(ino, name)) == NULL)
			return (NULL);
		ino = dp->d_ino;
	}
	return (dp);
}