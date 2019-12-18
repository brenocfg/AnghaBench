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
 int EBUSY ; 
 int atomic_xchg (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  prd_usage ; 

__attribute__((used)) static int opal_prd_open(struct inode *inode, struct file *file)
{
	/*
	 * Prevent multiple (separate) processes from concurrent interactions
	 * with the FW PRD channel
	 */
	if (atomic_xchg(&prd_usage, 1) == 1)
		return -EBUSY;

	return 0;
}