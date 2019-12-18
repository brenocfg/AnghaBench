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
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 long pp_do_ioctl (struct file*,unsigned int,unsigned long) ; 
 int /*<<< orphan*/  pp_do_mutex ; 

__attribute__((used)) static long pp_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	long ret;

	mutex_lock(&pp_do_mutex);
	ret = pp_do_ioctl(file, cmd, arg);
	mutex_unlock(&pp_do_mutex);
	return ret;
}