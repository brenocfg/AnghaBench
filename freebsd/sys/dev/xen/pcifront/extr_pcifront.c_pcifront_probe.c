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
struct xenbus_device_id {int dummy; } ;
struct xenbus_device {int dummy; } ;
struct pcifront_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 struct pcifront_device* alloc_pdev (struct xenbus_device*) ; 
 int pcifront_publish_info (struct pcifront_device*) ; 
 int /*<<< orphan*/  put_pdev (struct pcifront_device*) ; 

__attribute__((used)) static int
pcifront_probe(struct xenbus_device *xdev,
			   const struct xenbus_device_id *id)
{
	int err = 0;
	struct pcifront_device *pdev;

	DPRINTF("xenbus probing\n");

	if ((pdev = alloc_pdev(xdev)) == NULL)
		goto out;

	err = pcifront_publish_info(pdev);

 out:
	if (err)
		put_pdev(pdev);
	return err;
}