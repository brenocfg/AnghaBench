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
typedef  int u_int8_t ;
typedef  int u_int32_t ;
typedef  int u_int16_t ;
typedef  int /*<<< orphan*/  u_int ;
struct tdfx_softc {int /*<<< orphan*/  dev; } ;
struct tdfx_pio_data {int device; int port; int size; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
#define  PCI_COMMAND_FREEBSD 132 
#define  SST1_PCI_SPECIAL1_FREEBSD 131 
#define  SST1_PCI_SPECIAL2_FREEBSD 130 
#define  SST1_PCI_SPECIAL3_FREEBSD 129 
#define  SST1_PCI_SPECIAL4_FREEBSD 128 
 int /*<<< orphan*/  copyin (int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ devclass_get_softc (int /*<<< orphan*/ ,int) ; 
 int pci_read_config (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int tdfx_count ; 
 int /*<<< orphan*/  tdfx_devclass ; 

__attribute__((used)) static int
tdfx_query_update(u_int cmd, struct tdfx_pio_data *piod)
{
	/* XXX Comment this later, after careful inspection and spring cleaning :) */
	/* Return vals */
	u_int8_t  ret_byte;
	u_int16_t ret_word;
	u_int32_t ret_dword;

	/* Port vals, mask */
	u_int32_t retval, preval, mask;
	struct tdfx_softc* tdfx_info = NULL;
			

	if((piod == NULL) || (piod->device >= (tdfx_count &
					0xf))) {
#ifdef DEBUG
		printf("tdfx: Bad struct or device in tdfx_query_update\n");
#endif
		return -EINVAL;
	}

	tdfx_info = (struct tdfx_softc*)devclass_get_softc(tdfx_devclass, 
			piod->device);
	if(tdfx_info == NULL) return -ENXIO;
	/* Code below this line in the fuction was taken from the 
	 * Linux driver and converted for freebsd. */

	/* Check the size for all the ports, to make sure stuff doesn't get messed up
	 * by poorly written clients */

	switch(piod->port) {
		case PCI_COMMAND_FREEBSD:
			if(piod->size != 2) return -EINVAL;
			break;
		case SST1_PCI_SPECIAL1_FREEBSD:
			if(piod->size != 4) return -EINVAL;
			break;
		case SST1_PCI_SPECIAL2_FREEBSD:
			if(piod->size != 4) return -EINVAL;
			break;
		case SST1_PCI_SPECIAL3_FREEBSD:
			if(piod->size != 4) return -EINVAL;
			break;
		case SST1_PCI_SPECIAL4_FREEBSD:
			if(piod->size != 4) return -EINVAL;
			break;
		default:
			return -EINVAL;
	}
	/* Read the current value */
	retval = pci_read_config(tdfx_info->dev, piod->port & ~3, 4);
			
	/* These set up a mask to use, since apparently they wanted to write 4 bytes
	 * at once to the ports */
	switch (piod->size) {
		case 1:
			copyin(piod->value, &ret_byte, 1);
			preval = ret_byte << (8 * (piod->port & 0x3));
			mask = 0xff << (8 * (piod->port & 0x3));
			break;
		case 2:
			copyin(piod->value, &ret_word, 2);
			preval = ret_word << (8 * (piod->port & 0x3));
			mask = 0xffff << (8 * (piod->port & 0x3));
			break;
		case 4:
			copyin(piod->value, &ret_dword, 4);
			preval = ret_dword;
			mask = ~0;
			break;
		default:
			return -EINVAL;
	}
	/* Finally, combine the values and write it to the port */
	retval = (retval & ~mask) | preval;
	pci_write_config(tdfx_info->dev, piod->port & ~3, retval, 4);
   
	return 0;
}