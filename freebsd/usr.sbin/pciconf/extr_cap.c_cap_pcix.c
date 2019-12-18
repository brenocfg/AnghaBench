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
struct pci_conf {int pc_hdr; int /*<<< orphan*/  pc_sel; } ;

/* Variables and functions */
 int PCIM_HDRTYPE ; 
 int PCIXM_STATUS_133CAP ; 
 int PCIXM_STATUS_266CAP ; 
 int PCIXM_STATUS_533CAP ; 
 int PCIXM_STATUS_64BIT ; 
 int PCIXM_STATUS_MAX_READ ; 
#define  PCIXM_STATUS_MAX_READ_1024 139 
#define  PCIXM_STATUS_MAX_READ_2048 138 
#define  PCIXM_STATUS_MAX_READ_4096 137 
#define  PCIXM_STATUS_MAX_READ_512 136 
 int PCIXM_STATUS_MAX_SPLITS ; 
#define  PCIXM_STATUS_MAX_SPLITS_1 135 
#define  PCIXM_STATUS_MAX_SPLITS_12 134 
#define  PCIXM_STATUS_MAX_SPLITS_16 133 
#define  PCIXM_STATUS_MAX_SPLITS_2 132 
#define  PCIXM_STATUS_MAX_SPLITS_3 131 
#define  PCIXM_STATUS_MAX_SPLITS_32 130 
#define  PCIXM_STATUS_MAX_SPLITS_4 129 
#define  PCIXM_STATUS_MAX_SPLITS_8 128 
 scalar_t__ PCIXR_STATUS ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int read_config (int,int /*<<< orphan*/ *,scalar_t__,int) ; 

__attribute__((used)) static void
cap_pcix(int fd, struct pci_conf *p, uint8_t ptr)
{
	uint32_t status;
	int comma, max_splits, max_burst_read;

	status = read_config(fd, &p->pc_sel, ptr + PCIXR_STATUS, 4);
	printf("PCI-X ");
	if (status & PCIXM_STATUS_64BIT)
		printf("64-bit ");
	if ((p->pc_hdr & PCIM_HDRTYPE) == 1)
		printf("bridge ");
	if ((p->pc_hdr & PCIM_HDRTYPE) != 1 || (status & (PCIXM_STATUS_133CAP |
	    PCIXM_STATUS_266CAP | PCIXM_STATUS_533CAP)) != 0)
		printf("supports");
	comma = 0;
	if (status & PCIXM_STATUS_133CAP) {
		printf(" 133MHz");
		comma = 1;
	}
	if (status & PCIXM_STATUS_266CAP) {
		printf("%s 266MHz", comma ? "," : "");
		comma = 1;
	}
	if (status & PCIXM_STATUS_533CAP) {
		printf("%s 533MHz", comma ? "," : "");
		comma = 1;
	}
	if ((p->pc_hdr & PCIM_HDRTYPE) == 1)
		return;
	max_burst_read = 0;
	switch (status & PCIXM_STATUS_MAX_READ) {
	case PCIXM_STATUS_MAX_READ_512:
		max_burst_read = 512;
		break;
	case PCIXM_STATUS_MAX_READ_1024:
		max_burst_read = 1024;
		break;
	case PCIXM_STATUS_MAX_READ_2048:
		max_burst_read = 2048;
		break;
	case PCIXM_STATUS_MAX_READ_4096:
		max_burst_read = 4096;
		break;
	}
	max_splits = 0;
	switch (status & PCIXM_STATUS_MAX_SPLITS) {
	case PCIXM_STATUS_MAX_SPLITS_1:
		max_splits = 1;
		break;
	case PCIXM_STATUS_MAX_SPLITS_2:
		max_splits = 2;
		break;
	case PCIXM_STATUS_MAX_SPLITS_3:
		max_splits = 3;
		break;
	case PCIXM_STATUS_MAX_SPLITS_4:
		max_splits = 4;
		break;
	case PCIXM_STATUS_MAX_SPLITS_8:
		max_splits = 8;
		break;
	case PCIXM_STATUS_MAX_SPLITS_12:
		max_splits = 12;
		break;
	case PCIXM_STATUS_MAX_SPLITS_16:
		max_splits = 16;
		break;
	case PCIXM_STATUS_MAX_SPLITS_32:
		max_splits = 32;
		break;
	}
	printf("%s %d burst read, %d split transaction%s", comma ? "," : "",
	    max_burst_read, max_splits, max_splits == 1 ? "" : "s");
}