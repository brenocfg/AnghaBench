#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {char* desc; scalar_t__ class; int subclass; int report; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_cfg_save (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 char* pci_describe_device (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_class (int /*<<< orphan*/ ) ; 
 int pci_get_function (int /*<<< orphan*/ ) ; 
 int pci_get_slot (int /*<<< orphan*/ ) ; 
 int pci_get_subclass (int /*<<< orphan*/ ) ; 
 TYPE_1__* pci_nomatch_tab ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 

void
pci_probe_nomatch(device_t dev, device_t child)
{
	int i, report;
	const char *cp, *scp;
	char *device;

	/*
	 * Look for a listing for this device in a loaded device database.
	 */
	report = 1;
	if ((device = pci_describe_device(child)) != NULL) {
		device_printf(dev, "<%s>", device);
		free(device, M_DEVBUF);
	} else {
		/*
		 * Scan the class/subclass descriptions for a general
		 * description.
		 */
		cp = "unknown";
		scp = NULL;
		for (i = 0; pci_nomatch_tab[i].desc != NULL; i++) {
			if (pci_nomatch_tab[i].class == pci_get_class(child)) {
				if (pci_nomatch_tab[i].subclass == -1) {
					cp = pci_nomatch_tab[i].desc;
					report = pci_nomatch_tab[i].report;
				} else if (pci_nomatch_tab[i].subclass ==
				    pci_get_subclass(child)) {
					scp = pci_nomatch_tab[i].desc;
					report = pci_nomatch_tab[i].report;
				}
			}
		}
		if (report || bootverbose) {
			device_printf(dev, "<%s%s%s>",
			    cp ? cp : "",
			    ((cp != NULL) && (scp != NULL)) ? ", " : "",
			    scp ? scp : "");
		}
	}
	if (report || bootverbose) {
		printf(" at device %d.%d (no driver attached)\n",
		    pci_get_slot(child), pci_get_function(child));
	}
	pci_cfg_save(child, device_get_ivars(child), 1);
}