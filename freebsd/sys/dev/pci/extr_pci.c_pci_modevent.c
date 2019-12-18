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
struct cdev {int dummy; } ;
typedef  int /*<<< orphan*/  module_t ;
typedef  int /*<<< orphan*/ * eventhandler_tag ;

/* Variables and functions */
 int /*<<< orphan*/  EVENTHANDLER_DEREGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  GID_WHEEL ; 
#define  MOD_LOAD 129 
#define  MOD_UNLOAD 128 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  destroy_dev (struct cdev*) ; 
 int /*<<< orphan*/  dev_lookup ; 
 struct cdev* make_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  pci_devq ; 
 int /*<<< orphan*/  pci_generation ; 
 int /*<<< orphan*/  pci_load_vendor_data () ; 
 int /*<<< orphan*/  pci_lookup ; 
 int /*<<< orphan*/  pcicdev ; 

__attribute__((used)) static int
pci_modevent(module_t mod, int what, void *arg)
{
	static struct cdev *pci_cdev;
	static eventhandler_tag tag;

	switch (what) {
	case MOD_LOAD:
		STAILQ_INIT(&pci_devq);
		pci_generation = 0;
		pci_cdev = make_dev(&pcicdev, 0, UID_ROOT, GID_WHEEL, 0644,
		    "pci");
		pci_load_vendor_data();
		tag = EVENTHANDLER_REGISTER(dev_lookup, pci_lookup, NULL,
		    1000);
		break;

	case MOD_UNLOAD:
		if (tag != NULL)
			EVENTHANDLER_DEREGISTER(dev_lookup, tag);
		destroy_dev(pci_cdev);
		break;
	}

	return (0);
}