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

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
#define  NVME_CR_ACQ_HI 140 
#define  NVME_CR_ACQ_LOW 139 
#define  NVME_CR_AQA 138 
#define  NVME_CR_ASQ_HI 137 
#define  NVME_CR_ASQ_LOW 136 
#define  NVME_CR_CAP_HI 135 
#define  NVME_CR_CAP_LOW 134 
#define  NVME_CR_CC 133 
#define  NVME_CR_CSTS 132 
#define  NVME_CR_INTMC 131 
#define  NVME_CR_INTMS 130 
#define  NVME_CR_NSSR 129 
#define  NVME_CR_VS 128 

__attribute__((used)) static void
pci_nvme_bar0_reg_dumps(const char *func, uint64_t offset, int iswrite)
{
	const char *s = iswrite ? "WRITE" : "READ";

	switch (offset) {
	case NVME_CR_CAP_LOW:
		DPRINTF(("%s %s NVME_CR_CAP_LOW\r\n", func, s));
		break;
	case NVME_CR_CAP_HI:
		DPRINTF(("%s %s NVME_CR_CAP_HI\r\n", func, s));
		break;
	case NVME_CR_VS:
		DPRINTF(("%s %s NVME_CR_VS\r\n", func, s));
		break;
	case NVME_CR_INTMS:
		DPRINTF(("%s %s NVME_CR_INTMS\r\n", func, s));
		break;
	case NVME_CR_INTMC:
		DPRINTF(("%s %s NVME_CR_INTMC\r\n", func, s));
		break;
	case NVME_CR_CC:
		DPRINTF(("%s %s NVME_CR_CC\r\n", func, s));
		break;
	case NVME_CR_CSTS:
		DPRINTF(("%s %s NVME_CR_CSTS\r\n", func, s));
		break;
	case NVME_CR_NSSR:
		DPRINTF(("%s %s NVME_CR_NSSR\r\n", func, s));
		break;
	case NVME_CR_AQA:
		DPRINTF(("%s %s NVME_CR_AQA\r\n", func, s));
		break;
	case NVME_CR_ASQ_LOW:
		DPRINTF(("%s %s NVME_CR_ASQ_LOW\r\n", func, s));
		break;
	case NVME_CR_ASQ_HI:
		DPRINTF(("%s %s NVME_CR_ASQ_HI\r\n", func, s));
		break;
	case NVME_CR_ACQ_LOW:
		DPRINTF(("%s %s NVME_CR_ACQ_LOW\r\n", func, s));
		break;
	case NVME_CR_ACQ_HI:
		DPRINTF(("%s %s NVME_CR_ACQ_HI\r\n", func, s));
		break;
	default:
		DPRINTF(("unknown nvme bar-0 offset 0x%lx\r\n", offset));
	}

}