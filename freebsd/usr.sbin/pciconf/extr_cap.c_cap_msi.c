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
typedef  int uint16_t ;
struct pci_conf {int /*<<< orphan*/  pc_sel; } ;

/* Variables and functions */
 int PCIM_MSICTRL_64BIT ; 
 int PCIM_MSICTRL_MMC_MASK ; 
 int PCIM_MSICTRL_MME_MASK ; 
 int PCIM_MSICTRL_MSI_ENABLE ; 
 int PCIM_MSICTRL_VECTOR ; 
 scalar_t__ PCIR_MSI_CTRL ; 
 int /*<<< orphan*/  printf (char*,int,char*,...) ; 
 int read_config (int,int /*<<< orphan*/ *,scalar_t__,int) ; 

__attribute__((used)) static void
cap_msi(int fd, struct pci_conf *p, uint8_t ptr)
{
	uint16_t ctrl;
	int msgnum;

	ctrl = read_config(fd, &p->pc_sel, ptr + PCIR_MSI_CTRL, 2);
	msgnum = 1 << ((ctrl & PCIM_MSICTRL_MMC_MASK) >> 1);
	printf("MSI supports %d message%s%s%s ", msgnum,
	    (msgnum == 1) ? "" : "s",
	    (ctrl & PCIM_MSICTRL_64BIT) ? ", 64 bit" : "",
	    (ctrl & PCIM_MSICTRL_VECTOR) ? ", vector masks" : "");
	if (ctrl & PCIM_MSICTRL_MSI_ENABLE) {
		msgnum = 1 << ((ctrl & PCIM_MSICTRL_MME_MASK) >> 4);
		printf("enabled with %d message%s", msgnum,
		    (msgnum == 1) ? "" : "s");
	}
}