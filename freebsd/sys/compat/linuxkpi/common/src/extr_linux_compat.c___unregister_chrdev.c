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
struct linux_cdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cdev_del (struct linux_cdev*) ; 
 struct linux_cdev* linux_find_cdev (char const*,unsigned int,int) ; 

void
__unregister_chrdev(unsigned int major, unsigned int baseminor,
    unsigned int count, const char *name)
{
	struct linux_cdev *cdevp;
	int i;

	for (i = baseminor; i < baseminor + count; i++) {
		cdevp = linux_find_cdev(name, major, i);
		if (cdevp != NULL)
			cdev_del(cdevp);
	}
}