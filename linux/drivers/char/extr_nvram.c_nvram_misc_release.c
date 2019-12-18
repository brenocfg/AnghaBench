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
struct inode {int dummy; } ;
struct file {int f_mode; } ;

/* Variables and functions */
 int FMODE_WRITE ; 
 int NVRAM_EXCL ; 
 int NVRAM_WRITE ; 
 int /*<<< orphan*/  nvram_open_cnt ; 
 int nvram_open_mode ; 
 int /*<<< orphan*/  nvram_state_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nvram_misc_release(struct inode *inode, struct file *file)
{
	spin_lock(&nvram_state_lock);

	nvram_open_cnt--;

	/* if only one instance is open, clear the EXCL bit */
	if (nvram_open_mode & NVRAM_EXCL)
		nvram_open_mode &= ~NVRAM_EXCL;
	if (file->f_mode & FMODE_WRITE)
		nvram_open_mode &= ~NVRAM_WRITE;

	spin_unlock(&nvram_state_lock);

	return 0;
}