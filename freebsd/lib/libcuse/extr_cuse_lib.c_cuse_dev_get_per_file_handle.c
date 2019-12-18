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
struct cuse_dev_entered {void* per_file_handle; struct cuse_dev* cdev; } ;
struct cuse_dev {int dummy; } ;

/* Variables and functions */
 struct cuse_dev_entered* cuse_dev_get_entered () ; 

void   *
cuse_dev_get_per_file_handle(struct cuse_dev *cdev)
{
	struct cuse_dev_entered *pe;

	pe = cuse_dev_get_entered();
	if (pe == NULL || pe->cdev != cdev)
		return (NULL);

	return (pe->per_file_handle);
}