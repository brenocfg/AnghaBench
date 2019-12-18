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
struct inode {int /*<<< orphan*/  i_rdev; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int DEVCOUNT ; 
 int EALREADY ; 
 int ENOENT ; 
 int MINOR (int /*<<< orphan*/ ) ; 
 scalar_t__ openCnt ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 

__attribute__((used)) static int gio_open(struct inode *inode, struct file *filp)
{
	int minor;
	int ret = -ENOENT;

	preempt_disable();
	minor = MINOR(inode->i_rdev);
	if (minor < DEVCOUNT) {
		if (openCnt > 0) {
			ret = -EALREADY;
		} else {
			openCnt++;
			ret = 0;
		}
	}
	preempt_enable();
	return ret;
}