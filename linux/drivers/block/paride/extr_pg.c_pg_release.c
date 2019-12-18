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
struct pg {int /*<<< orphan*/  access; int /*<<< orphan*/ * bufptr; } ;
struct inode {int dummy; } ;
struct file {struct pg* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pg_release(struct inode *inode, struct file *file)
{
	struct pg *dev = file->private_data;

	kfree(dev->bufptr);
	dev->bufptr = NULL;
	clear_bit(0, &dev->access);

	return 0;
}