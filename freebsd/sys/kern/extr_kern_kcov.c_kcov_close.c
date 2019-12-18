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
struct thread {int dummy; } ;
struct kcov_info {scalar_t__ state; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ KCOV_STATE_RUNNING ; 
 int devfs_get_cdevpriv (void**) ; 

__attribute__((used)) static int
kcov_close(struct cdev *dev, int fflag, int devtype, struct thread *td)
{
	struct kcov_info *info;
	int error;


	if ((error = devfs_get_cdevpriv((void **)&info)) != 0)
		return (error);

	KASSERT(info != NULL, ("kcov_close with no kcov_info structure"));

	/* Trying to close, but haven't disabled */
	if (info->state == KCOV_STATE_RUNNING)
		return (EBUSY);

	return (0);
}