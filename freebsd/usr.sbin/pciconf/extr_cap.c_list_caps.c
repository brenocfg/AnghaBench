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
#define  PCIM_HDRTYPE_BRIDGE 144 
#define  PCIM_HDRTYPE_CARDBUS 143 
#define  PCIM_HDRTYPE_NORMAL 142 
 int PCIM_STATUS_CAPPRESENT ; 
 int PCIR_CAP_PTR ; 
 int PCIR_CAP_PTR_2 ; 
 int PCIR_STATUS ; 
#define  PCIY_AGP 141 
#define  PCIY_DEBUG 140 
#define  PCIY_EA 139 
#define  PCIY_EXPRESS 138 
#define  PCIY_HT 137 
#define  PCIY_MSI 136 
#define  PCIY_MSIX 135 
#define  PCIY_PCIAF 134 
#define  PCIY_PCIX 133 
#define  PCIY_PMG 132 
#define  PCIY_SATA 131 
#define  PCIY_SUBVENDOR 130 
#define  PCIY_VENDOR 129 
#define  PCIY_VPD 128 
 int /*<<< orphan*/  cap_agp (int,struct pci_conf*,int) ; 
 int /*<<< orphan*/  cap_debug (int,struct pci_conf*,int) ; 
 int /*<<< orphan*/  cap_ea (int,struct pci_conf*,int) ; 
 int /*<<< orphan*/  cap_express (int,struct pci_conf*,int) ; 
 int /*<<< orphan*/  cap_ht (int,struct pci_conf*,int) ; 
 int /*<<< orphan*/  cap_msi (int,struct pci_conf*,int) ; 
 int /*<<< orphan*/  cap_msix (int,struct pci_conf*,int) ; 
 int /*<<< orphan*/  cap_pciaf (int,struct pci_conf*,int) ; 
 int /*<<< orphan*/  cap_pcix (int,struct pci_conf*,int) ; 
 int /*<<< orphan*/  cap_power (int,struct pci_conf*,int) ; 
 int /*<<< orphan*/  cap_sata (int,struct pci_conf*,int) ; 
 int /*<<< orphan*/  cap_subvendor (int,struct pci_conf*,int) ; 
 int /*<<< orphan*/  cap_vendor (int,struct pci_conf*,int) ; 
 int /*<<< orphan*/  cap_vpd (int,struct pci_conf*,int) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  list_ecaps (int,struct pci_conf*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 void* read_config (int,int /*<<< orphan*/ *,int,int) ; 

void
list_caps(int fd, struct pci_conf *p)
{
	int express;
	uint16_t sta;
	uint8_t ptr, cap;

	/* Are capabilities present for this device? */
	sta = read_config(fd, &p->pc_sel, PCIR_STATUS, 2);
	if (!(sta & PCIM_STATUS_CAPPRESENT))
		return;

	switch (p->pc_hdr & PCIM_HDRTYPE) {
	case PCIM_HDRTYPE_NORMAL:
	case PCIM_HDRTYPE_BRIDGE:
		ptr = PCIR_CAP_PTR;
		break;
	case PCIM_HDRTYPE_CARDBUS:
		ptr = PCIR_CAP_PTR_2;
		break;
	default:
		errx(1, "list_caps: bad header type");
	}

	/* Walk the capability list. */
	express = 0;
	ptr = read_config(fd, &p->pc_sel, ptr, 1);
	while (ptr != 0 && ptr != 0xff) {
		cap = read_config(fd, &p->pc_sel, ptr + PCICAP_ID, 1);
		printf("    cap %02x[%02x] = ", cap, ptr);
		switch (cap) {
		case PCIY_PMG:
			cap_power(fd, p, ptr);
			break;
		case PCIY_AGP:
			cap_agp(fd, p, ptr);
			break;
		case PCIY_VPD:
			cap_vpd(fd, p, ptr);
			break;
		case PCIY_MSI:
			cap_msi(fd, p, ptr);
			break;
		case PCIY_PCIX:
			cap_pcix(fd, p, ptr);
			break;
		case PCIY_HT:
			cap_ht(fd, p, ptr);
			break;
		case PCIY_VENDOR:
			cap_vendor(fd, p, ptr);
			break;
		case PCIY_DEBUG:
			cap_debug(fd, p, ptr);
			break;
		case PCIY_SUBVENDOR:
			cap_subvendor(fd, p, ptr);
			break;
		case PCIY_EXPRESS:
			express = 1;
			cap_express(fd, p, ptr);
			break;
		case PCIY_MSIX:
			cap_msix(fd, p, ptr);
			break;
		case PCIY_SATA:
			cap_sata(fd, p, ptr);
			break;
		case PCIY_PCIAF:
			cap_pciaf(fd, p, ptr);
			break;
		case PCIY_EA:
			cap_ea(fd, p, ptr);
			break;
		default:
			printf("unknown");
			break;
		}
		printf("\n");
		ptr = read_config(fd, &p->pc_sel, ptr + PCICAP_NEXTPTR, 1);
	}

	if (express)
		list_ecaps(fd, p);
}