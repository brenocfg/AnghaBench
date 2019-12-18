#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dirent {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dd_lock; } ;
typedef  TYPE_1__ DIR ;

/* Variables and functions */
 int RDU_SHORT ; 
 int RDU_SKIP ; 
 int /*<<< orphan*/  _GENERIC_DIRSIZ (struct dirent*) ; 
 scalar_t__ __isthreaded ; 
 int /*<<< orphan*/  _pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 struct dirent* _readdir_unlocked (TYPE_1__*,int) ; 
 int errno ; 
 int /*<<< orphan*/  memcpy (struct dirent*,struct dirent*,int /*<<< orphan*/ ) ; 

int
__readdir_r(DIR *dirp, struct dirent *entry, struct dirent **result)
{
	struct dirent *dp;
	int saved_errno;

	saved_errno = errno;
	errno = 0;
	if (__isthreaded)
		_pthread_mutex_lock(&dirp->dd_lock);
	dp = _readdir_unlocked(dirp, RDU_SKIP | RDU_SHORT);
	if (dp != NULL)
		memcpy(entry, dp, _GENERIC_DIRSIZ(dp));
	if (__isthreaded)
		_pthread_mutex_unlock(&dirp->dd_lock);

	if (errno != 0) {
		if (dp == NULL)
			return (errno);
	} else
		errno = saved_errno;

	if (dp != NULL)
		*result = entry;
	else
		*result = NULL;

	return (0);
}