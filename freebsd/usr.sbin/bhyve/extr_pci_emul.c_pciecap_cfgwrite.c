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
typedef  int /*<<< orphan*/  uint32_t ;
struct pci_devinst {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFGWRITE (struct pci_devinst*,int,int /*<<< orphan*/ ,int) ; 

void
pciecap_cfgwrite(struct pci_devinst *pi, int capoff, int offset,
		 int bytes, uint32_t val)
{

	/* XXX don't write to the readonly parts */
	CFGWRITE(pi, offset, val, bytes);
}