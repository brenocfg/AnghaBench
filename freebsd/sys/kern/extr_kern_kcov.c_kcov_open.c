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
struct kcov_info {int mode; int /*<<< orphan*/ * thread; int /*<<< orphan*/  state; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KCOV_STATE_OPEN ; 
 int /*<<< orphan*/  M_KCOV_INFO ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int devfs_set_cdevpriv (struct kcov_info*,int /*<<< orphan*/  (*) (struct kcov_info*)) ; 
 int /*<<< orphan*/  kcov_mmap_cleanup (struct kcov_info*) ; 
 struct kcov_info* malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
kcov_open(struct cdev *dev, int oflags, int devtype, struct thread *td)
{
	struct kcov_info *info;
	int error;

	info = malloc(sizeof(struct kcov_info), M_KCOV_INFO, M_ZERO | M_WAITOK);
	info->state = KCOV_STATE_OPEN;
	info->thread = NULL;
	info->mode = -1;

	if ((error = devfs_set_cdevpriv(info, kcov_mmap_cleanup)) != 0)
		kcov_mmap_cleanup(info);

	return (error);
}