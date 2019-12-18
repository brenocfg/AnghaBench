#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct file {int f_flags; int f_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/ * set_checksum; } ;

/* Variables and functions */
 int EBUSY ; 
 int FMODE_WRITE ; 
 int NVRAM_EXCL ; 
 int NVRAM_WRITE ; 
 int O_EXCL ; 
 TYPE_1__ arch_nvram_ops ; 
 scalar_t__ nvram_open_cnt ; 
 int nvram_open_mode ; 
 int /*<<< orphan*/  nvram_state_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nvram_misc_open(struct inode *inode, struct file *file)
{
	spin_lock(&nvram_state_lock);

	/* Prevent multiple readers/writers if desired. */
	if ((nvram_open_cnt && (file->f_flags & O_EXCL)) ||
	    (nvram_open_mode & NVRAM_EXCL)) {
		spin_unlock(&nvram_state_lock);
		return -EBUSY;
	}

#if defined(CONFIG_X86) || defined(CONFIG_M68K)
	/* Prevent multiple writers if the set_checksum ioctl is implemented. */
	if ((arch_nvram_ops.set_checksum != NULL) &&
	    (file->f_mode & FMODE_WRITE) && (nvram_open_mode & NVRAM_WRITE)) {
		spin_unlock(&nvram_state_lock);
		return -EBUSY;
	}
#endif

	if (file->f_flags & O_EXCL)
		nvram_open_mode |= NVRAM_EXCL;
	if (file->f_mode & FMODE_WRITE)
		nvram_open_mode |= NVRAM_WRITE;
	nvram_open_cnt++;

	spin_unlock(&nvram_state_lock);

	return 0;
}