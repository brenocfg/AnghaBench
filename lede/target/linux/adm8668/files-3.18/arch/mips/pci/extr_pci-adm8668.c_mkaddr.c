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
typedef  int u32 ;
struct pci_bus {int number; } ;

/* Variables and functions */

__attribute__((used)) static inline u32 mkaddr(struct pci_bus *bus, unsigned int devfn, int where)
{
	return ((bus->number & 0xff) << 16) | ((devfn & 0xff) << 8) |
		(where & 0xfc);
}