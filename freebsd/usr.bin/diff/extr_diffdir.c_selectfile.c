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
struct excludes {int /*<<< orphan*/  pattern; struct excludes* next; } ;
struct dirent {scalar_t__ d_fileno; char* d_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  FNM_PATHNAME ; 
 struct excludes* excludes_list ; 
 scalar_t__ fnmatch (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
selectfile(const struct dirent *dp)
{
	struct excludes *excl;

	if (dp->d_fileno == 0)
		return (0);

	/* always skip "." and ".." */
	if (dp->d_name[0] == '.' && (dp->d_name[1] == '\0' ||
	    (dp->d_name[1] == '.' && dp->d_name[2] == '\0')))
		return (0);

	/* check excludes list */
	for (excl = excludes_list; excl != NULL; excl = excl->next)
		if (fnmatch(excl->pattern, dp->d_name, FNM_PATHNAME) == 0)
			return (0);

	return (1);
}