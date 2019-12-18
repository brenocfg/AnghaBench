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
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int /*<<< orphan*/  u_int16_t ;
typedef  int /*<<< orphan*/  u_int ;
struct tdfx_softc {int /*<<< orphan*/  dev; int /*<<< orphan*/  addr1; int /*<<< orphan*/  addr0; int /*<<< orphan*/  type; int /*<<< orphan*/  vendor; } ;
struct tdfx_pio_data {scalar_t__ device; int port; int size; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
#define  PCI_BASE_ADDRESS_0_FREEBSD 137 
#define  PCI_BASE_ADDRESS_1_FREEBSD 136 
#define  PCI_DEVICE_ID_FREEBSD 135 
#define  PCI_IOBASE_0_FREEBSD 134 
#define  PCI_IOLIMIT_0_FREEBSD 133 
#define  PCI_PRIBUS_FREEBSD 132 
#define  PCI_REVISION_ID_FREEBSD 131 
#define  PCI_VENDOR_ID_FREEBSD 130 
#define  SST1_PCI_SPECIAL1_FREEBSD 129 
#define  SST1_PCI_SPECIAL4_FREEBSD 128 
 int /*<<< orphan*/  copyout (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ devclass_get_softc (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pci_read_config (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ tdfx_count ; 
 int /*<<< orphan*/  tdfx_devclass ; 

__attribute__((used)) static int
tdfx_query_fetch(u_int cmd, struct tdfx_pio_data *piod)
{
	/* XXX Comment this later, after careful inspection and spring cleaning :) */
	/* Various return values 8bit-32bit */
	u_int8_t  ret_byte;
	u_int16_t ret_word;
	u_int32_t ret_dword;
	struct tdfx_softc* tdfx_info = NULL;	

	/* This one depend on the tdfx_* structs being properly initialized */

	/*piod->device &= 0xf;*/
	if((piod == NULL) ||(tdfx_count <= piod->device) ||
			(piod->device < 0)) {
#ifdef DEBUG
		printf("tdfx: Bad device or internal struct in tdfx_query_fetch\n");
#endif
		return -EINVAL;
	}

	tdfx_info = (struct tdfx_softc*)devclass_get_softc(tdfx_devclass,
			piod->device);

	if(tdfx_info == NULL) return -ENXIO;

	/* We must restrict the size reads from the port, since to high or low of a
	 * size witll result in wrong data being passed, and that's bad */
	/* A few of these were pulled during the attach phase */
	switch(piod->port) {
		case PCI_VENDOR_ID_FREEBSD:
			if(piod->size != 2) return -EINVAL;
			copyout(&tdfx_info->vendor, piod->value, piod->size);
			return 0;
		case PCI_DEVICE_ID_FREEBSD:
			if(piod->size != 2) return -EINVAL;
			copyout(&tdfx_info->type, piod->value, piod->size);
			return 0;
		case PCI_BASE_ADDRESS_0_FREEBSD:
			if(piod->size != 4) return -EINVAL;
			copyout(&tdfx_info->addr0, piod->value, piod->size);
			return 0;
		case PCI_BASE_ADDRESS_1_FREEBSD:
			if(piod->size != 4) return -EINVAL;
			copyout(&tdfx_info->addr1, piod->value, piod->size);
			return 0;
		case PCI_PRIBUS_FREEBSD:
			if(piod->size != 1) return -EINVAL;
			break;
		case PCI_IOBASE_0_FREEBSD:
			if(piod->size != 2) return -EINVAL;
			break;
		case PCI_IOLIMIT_0_FREEBSD:
			if(piod->size != 2) return -EINVAL;
			break;
		case SST1_PCI_SPECIAL1_FREEBSD:
			if(piod->size != 4) return -EINVAL;
			break;
		case PCI_REVISION_ID_FREEBSD:
			if(piod->size != 1) return -EINVAL;
			break;
		case SST1_PCI_SPECIAL4_FREEBSD:
			if(piod->size != 4) return -EINVAL;
			break;
		default:
			return -EINVAL;
	}

	
	/* Read the value and return */
	switch(piod->size) {
		case 1:
			ret_byte = pci_read_config(tdfx_info[piod->device].dev, 
					piod->port, 1);
			copyout(&ret_byte, piod->value, 1);
			break;
		case 2:
			ret_word = pci_read_config(tdfx_info[piod->device].dev, 
					piod->port, 2);
			copyout(&ret_word, piod->value, 2);
			break;
		case 4:
			ret_dword = pci_read_config(tdfx_info[piod->device].dev, 
					piod->port, 4);
			copyout(&ret_dword, piod->value, 4);
			break;
		default:
			return -EINVAL;
	}
	return 0;
}