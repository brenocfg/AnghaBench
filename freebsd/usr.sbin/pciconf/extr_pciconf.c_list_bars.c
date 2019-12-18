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
struct pci_conf {int pc_hdr; } ;

/* Variables and functions */
 int PCIM_HDRTYPE ; 
#define  PCIM_HDRTYPE_BRIDGE 130 
#define  PCIM_HDRTYPE_CARDBUS 129 
#define  PCIM_HDRTYPE_NORMAL 128 
 int /*<<< orphan*/  PCIR_BAR (int) ; 
 int PCIR_MAX_BAR_0 ; 
 int PCIR_MAX_BAR_1 ; 
 int PCIR_MAX_BAR_2 ; 
 int /*<<< orphan*/  print_bar (int,struct pci_conf*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
list_bars(int fd, struct pci_conf *p)
{
	int i, max;

	switch (p->pc_hdr & PCIM_HDRTYPE) {
	case PCIM_HDRTYPE_NORMAL:
		max = PCIR_MAX_BAR_0;
		break;
	case PCIM_HDRTYPE_BRIDGE:
		max = PCIR_MAX_BAR_1;
		break;
	case PCIM_HDRTYPE_CARDBUS:
		max = PCIR_MAX_BAR_2;
		break;
	default:
		return;
	}

	for (i = 0; i <= max; i++)
		print_bar(fd, p, "bar   ", PCIR_BAR(i));
}