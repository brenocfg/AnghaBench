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
struct parport_driver {char* name; int devmodel; int /*<<< orphan*/  probe; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct parport_driver*) ; 
 struct parport_driver* kzalloc (int,int /*<<< orphan*/ ) ; 
 int parport_register_driver (struct parport_driver*) ; 
 int /*<<< orphan*/  pi_probe ; 

void *pi_register_driver(char *name)
{
	struct parport_driver *parp_drv;
	int ret;

	parp_drv = kzalloc(sizeof(*parp_drv), GFP_KERNEL);
	if (!parp_drv)
		return NULL;

	parp_drv->name = name;
	parp_drv->probe = pi_probe;
	parp_drv->devmodel = true;

	ret = parport_register_driver(parp_drv);
	if (ret) {
		kfree(parp_drv);
		return NULL;
	}
	return (void *)parp_drv;
}