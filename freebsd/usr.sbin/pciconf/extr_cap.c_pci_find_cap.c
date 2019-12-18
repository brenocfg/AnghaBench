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
typedef  int uint8_t ;
typedef  int uint16_t ;
struct pci_conf {int pc_hdr; int /*<<< orphan*/  pc_sel; } ;

/* Variables and functions */
 int PCICAP_ID ; 
 int PCICAP_NEXTPTR ; 
 int PCIM_HDRTYPE ; 
#define  PCIM_HDRTYPE_BRIDGE 130 
#define  PCIM_HDRTYPE_CARDBUS 129 
#define  PCIM_HDRTYPE_NORMAL 128 
 int PCIM_STATUS_CAPPRESENT ; 
 int PCIR_CAP_PTR ; 
 int PCIR_CAP_PTR_2 ; 
 int PCIR_STATUS ; 
 void* read_config (int,int /*<<< orphan*/ *,int,int) ; 

uint8_t
pci_find_cap(int fd, struct pci_conf *p, uint8_t id)
{
	uint16_t sta;
	uint8_t ptr, cap;

	/* Are capabilities present for this device? */
	sta = read_config(fd, &p->pc_sel, PCIR_STATUS, 2);
	if (!(sta & PCIM_STATUS_CAPPRESENT))
		return (0);

	switch (p->pc_hdr & PCIM_HDRTYPE) {
	case PCIM_HDRTYPE_NORMAL:
	case PCIM_HDRTYPE_BRIDGE:
		ptr = PCIR_CAP_PTR;
		break;
	case PCIM_HDRTYPE_CARDBUS:
		ptr = PCIR_CAP_PTR_2;
		break;
	default:
		return (0);
	}

	ptr = read_config(fd, &p->pc_sel, ptr, 1);
	while (ptr != 0 && ptr != 0xff) {
		cap = read_config(fd, &p->pc_sel, ptr + PCICAP_ID, 1);
		if (cap == id)
			return (ptr);
		ptr = read_config(fd, &p->pc_sel, ptr + PCICAP_NEXTPTR, 1);
	}
	return (0);
}