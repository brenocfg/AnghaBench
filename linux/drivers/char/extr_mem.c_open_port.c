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
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_RAWIO ; 
 int EPERM ; 
 int /*<<< orphan*/  LOCKDOWN_DEV_MEM ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int security_locked_down (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int open_port(struct inode *inode, struct file *filp)
{
	if (!capable(CAP_SYS_RAWIO))
		return -EPERM;

	return security_locked_down(LOCKDOWN_DEV_MEM);
}