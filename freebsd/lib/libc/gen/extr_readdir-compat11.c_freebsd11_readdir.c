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
struct freebsd11_dirent {int dummy; } ;
struct dirent {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dd_lock; struct freebsd11_dirent* dd_compat_de; } ;
typedef  TYPE_1__ DIR ;

/* Variables and functions */
 int /*<<< orphan*/  RDU_SKIP ; 
 scalar_t__ __isthreaded ; 
 int /*<<< orphan*/  _pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 struct dirent* _readdir_unlocked (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ freebsd11_cvtdirent (struct freebsd11_dirent*,struct dirent*) ; 
 struct freebsd11_dirent* malloc (int) ; 

struct freebsd11_dirent *
freebsd11_readdir(DIR *dirp)
{
	struct freebsd11_dirent *dstdp;
	struct dirent *dp;

	if (__isthreaded)
		_pthread_mutex_lock(&dirp->dd_lock);
	dp = _readdir_unlocked(dirp, RDU_SKIP);
	if (dp != NULL) {
		if (dirp->dd_compat_de == NULL)
			dirp->dd_compat_de = malloc(sizeof(struct
			    freebsd11_dirent));
		if (freebsd11_cvtdirent(dirp->dd_compat_de, dp))
			dstdp = dirp->dd_compat_de;
		else
			dstdp = NULL;
	} else
		dstdp = NULL;
	if (__isthreaded)
		_pthread_mutex_unlock(&dirp->dd_lock);

	return (dstdp);
}