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
typedef  scalar_t__ u_int16_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {scalar_t__ subvendor; scalar_t__ subdevice; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ PCID_ENVY24 ; 
 scalar_t__ PCIV_ENVY24 ; 
 TYPE_1__* cfg_table ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_device (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_subdevice (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_subvendor (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_vendor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
envy24_pci_probe(device_t dev)
{
	u_int16_t sv, sd;
	int i;

#if(0)
	printf("envy24_pci_probe()\n");
#endif
	if (pci_get_device(dev) == PCID_ENVY24 &&
	    pci_get_vendor(dev) == PCIV_ENVY24) {
		sv = pci_get_subvendor(dev);
		sd = pci_get_subdevice(dev);
		for (i = 0; cfg_table[i].subvendor != 0 || cfg_table[i].subdevice != 0; i++) {
			if (cfg_table[i].subvendor == sv &&
			    cfg_table[i].subdevice == sd) {
				break;
			}
		}
		device_set_desc(dev, cfg_table[i].name);
#if(0)
		printf("envy24_pci_probe(): return 0\n");
#endif
		return 0;
	}
	else {
#if(0)
		printf("envy24_pci_probe(): return ENXIO\n");
#endif
		return ENXIO;
	}
}