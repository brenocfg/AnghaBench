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
struct pci_conf {int /*<<< orphan*/  pc_sel; } ;

/* Variables and functions */
 int PCIM_PCIAFCAP_FLR ; 
 int PCIM_PCIAFCAP_TP ; 
 int PCIR_PCIAF_CAP ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 int read_config (int,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void
cap_pciaf(int fd, struct pci_conf *p, uint8_t ptr)
{
	uint8_t cap;

	cap = read_config(fd, &p->pc_sel, ptr + PCIR_PCIAF_CAP, 1);
	printf("PCI Advanced Features:%s%s",
	    cap & PCIM_PCIAFCAP_FLR ? " FLR" : "",
	    cap & PCIM_PCIAFCAP_TP  ? " TP"  : "");
}