#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct resource {scalar_t__ start; } ;
struct TYPE_2__ {scalar_t__ m64_base; scalar_t__ m64_size; } ;
struct pnv_phb {TYPE_1__ ioda; } ;

/* Variables and functions */

__attribute__((used)) static inline bool pnv_pci_is_m64(struct pnv_phb *phb, struct resource *r)
{
	/*
	 * WARNING: We cannot rely on the resource flags. The Linux PCI
	 * allocation code sometimes decides to put a 64-bit prefetchable
	 * BAR in the 32-bit window, so we have to compare the addresses.
	 *
	 * For simplicity we only test resource start.
	 */
	return (r->start >= phb->ioda.m64_base &&
		r->start < (phb->ioda.m64_base + phb->ioda.m64_size));
}