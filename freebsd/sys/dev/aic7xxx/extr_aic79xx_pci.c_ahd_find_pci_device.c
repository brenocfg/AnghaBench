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
typedef  int uint64_t ;
typedef  scalar_t__ uint16_t ;
typedef  size_t u_int ;
struct ahd_pci_identity {int full_id; int id_mask; int /*<<< orphan*/ * name; } ;
typedef  int /*<<< orphan*/  aic_dev_softc_t ;

/* Variables and functions */
 scalar_t__ ADAPTECVENDORID ; 
 scalar_t__ DEVICE8081 ; 
 scalar_t__ DEVICE8088 ; 
 scalar_t__ DEVICE8089 ; 
 int ID_ALL_IROC_MASK ; 
 int /*<<< orphan*/  PCIR_DEVICE ; 
 int /*<<< orphan*/  PCIR_DEVVENDOR ; 
 int /*<<< orphan*/  PCIR_SUBDEV_0 ; 
 int /*<<< orphan*/  PCIR_SUBVEND_0 ; 
 scalar_t__ SUBVENDOR9005 ; 
 scalar_t__ ahd_attach_to_HostRAID_controllers ; 
 int ahd_compose_id (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 size_t ahd_num_pci_devs ; 
 struct ahd_pci_identity* ahd_pci_ident_table ; 
 scalar_t__ aic_pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

struct ahd_pci_identity *
ahd_find_pci_device(aic_dev_softc_t pci)
{
	uint64_t  full_id;
	uint16_t  device;
	uint16_t  vendor;
	uint16_t  subdevice;
	uint16_t  subvendor;
	struct	  ahd_pci_identity *entry;
	u_int	  i;

	vendor = aic_pci_read_config(pci, PCIR_DEVVENDOR, /*bytes*/2);
	device = aic_pci_read_config(pci, PCIR_DEVICE, /*bytes*/2);
	subvendor = aic_pci_read_config(pci, PCIR_SUBVEND_0, /*bytes*/2);
	subdevice = aic_pci_read_config(pci, PCIR_SUBDEV_0, /*bytes*/2);

	if ((vendor == ADAPTECVENDORID) && (subvendor == SUBVENDOR9005)) {
		if ((device == DEVICE8081) || (device == DEVICE8088) || 
			(device == DEVICE8089)) {
			printf("Controller device ID conflict with PMC Adaptec HBA\n");
			return (NULL);
		}
	}

	full_id = ahd_compose_id(device,
				 vendor,
				 subdevice,
				 subvendor);

	/*
	 * If we are configured to attach to HostRAID
	 * controllers, mask out the IROC/HostRAID bit
	 * in the 
	 */
	if (ahd_attach_to_HostRAID_controllers)
		full_id &= ID_ALL_IROC_MASK;

	for (i = 0; i < ahd_num_pci_devs; i++) {
		entry = &ahd_pci_ident_table[i];
		if (entry->full_id == (full_id & entry->id_mask)) {
			/* Honor exclusion entries. */
			if (entry->name == NULL)
				return (NULL);
			return (entry);
		}
	}
	return (NULL);
}