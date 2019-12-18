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
struct request {int dummy; } ;
struct loop_device {struct file* lo_backing_file; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 scalar_t__ unlikely (int) ; 
 int vfs_fsync (struct file*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lo_req_flush(struct loop_device *lo, struct request *rq)
{
	struct file *file = lo->lo_backing_file;
	int ret = vfs_fsync(file, 0);
	if (unlikely(ret && ret != -EINVAL))
		ret = -EIO;

	return ret;
}