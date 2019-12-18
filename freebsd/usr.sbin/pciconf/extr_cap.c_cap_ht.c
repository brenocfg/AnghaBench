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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct pci_conf {int /*<<< orphan*/  pc_sel; } ;

/* Variables and functions */
#define  PCIM_HTCAP_ADDRESS_MAPPING 142 
#define  PCIM_HTCAP_DIRECT_ROUTE 141 
#define  PCIM_HTCAP_EXT_CONFIG_SPACE 140 
#define  PCIM_HTCAP_FLE 139 
#define  PCIM_HTCAP_GEN3 138 
#define  PCIM_HTCAP_HIGH_NODE_COUNT 137 
 int PCIM_HTCAP_HOST ; 
#define  PCIM_HTCAP_INTERRUPT 136 
#define  PCIM_HTCAP_MSI_MAPPING 135 
#define  PCIM_HTCAP_PM 134 
#define  PCIM_HTCAP_RETRY_MODE 133 
#define  PCIM_HTCAP_REVISION_ID 132 
 int PCIM_HTCAP_SLAVE ; 
#define  PCIM_HTCAP_SWITCH 131 
#define  PCIM_HTCAP_UNITID_CLUMPING 130 
#define  PCIM_HTCAP_VCSET 129 
#define  PCIM_HTCAP_X86_ENCODING 128 
 int PCIM_HTCMD_CAP_MASK ; 
 int PCIM_HTCMD_MSI_ENABLE ; 
 int PCIM_HTCMD_MSI_FIXED ; 
 scalar_t__ PCIR_HTMSI_ADDRESS_HI ; 
 scalar_t__ PCIR_HTMSI_ADDRESS_LO ; 
 scalar_t__ PCIR_HT_COMMAND ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int read_config (int,int /*<<< orphan*/ *,scalar_t__,int) ; 

__attribute__((used)) static void
cap_ht(int fd, struct pci_conf *p, uint8_t ptr)
{
	uint32_t reg;
	uint16_t command;

	command = read_config(fd, &p->pc_sel, ptr + PCIR_HT_COMMAND, 2);
	printf("HT ");
	if ((command & 0xe000) == PCIM_HTCAP_SLAVE)
		printf("slave");
	else if ((command & 0xe000) == PCIM_HTCAP_HOST)
		printf("host");
	else
		switch (command & PCIM_HTCMD_CAP_MASK) {
		case PCIM_HTCAP_SWITCH:
			printf("switch");
			break;
		case PCIM_HTCAP_INTERRUPT:
			printf("interrupt");
			break;
		case PCIM_HTCAP_REVISION_ID:
			printf("revision ID");
			break;
		case PCIM_HTCAP_UNITID_CLUMPING:
			printf("unit ID clumping");
			break;
		case PCIM_HTCAP_EXT_CONFIG_SPACE:
			printf("extended config space");
			break;
		case PCIM_HTCAP_ADDRESS_MAPPING:
			printf("address mapping");
			break;
		case PCIM_HTCAP_MSI_MAPPING:
			printf("MSI %saddress window %s at 0x",
			    command & PCIM_HTCMD_MSI_FIXED ? "fixed " : "",
			    command & PCIM_HTCMD_MSI_ENABLE ? "enabled" :
			    "disabled");
			if (command & PCIM_HTCMD_MSI_FIXED)
				printf("fee00000");
			else {
				reg = read_config(fd, &p->pc_sel,
				    ptr + PCIR_HTMSI_ADDRESS_HI, 4);
				if (reg != 0)
					printf("%08x", reg);
				reg = read_config(fd, &p->pc_sel,
				    ptr + PCIR_HTMSI_ADDRESS_LO, 4);
				printf("%08x", reg);
			}
			break;
		case PCIM_HTCAP_DIRECT_ROUTE:
			printf("direct route");
			break;
		case PCIM_HTCAP_VCSET:
			printf("VC set");
			break;
		case PCIM_HTCAP_RETRY_MODE:
			printf("retry mode");
			break;
		case PCIM_HTCAP_X86_ENCODING:
			printf("X86 encoding");
			break;
		case PCIM_HTCAP_GEN3:
			printf("Gen3");
			break;
		case PCIM_HTCAP_FLE:
			printf("function-level extension");
			break;
		case PCIM_HTCAP_PM:
			printf("power management");
			break;
		case PCIM_HTCAP_HIGH_NODE_COUNT:
			printf("high node count");
			break;
		default:
			printf("unknown %02x", command);
			break;
		}
}