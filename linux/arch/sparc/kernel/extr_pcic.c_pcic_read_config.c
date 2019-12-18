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
typedef  unsigned int u32 ;
struct pci_bus {scalar_t__ number; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  pcic_read_config_dword (scalar_t__,unsigned int,int,unsigned int*) ; 

__attribute__((used)) static int pcic_read_config(struct pci_bus *bus, unsigned int devfn,
   int where, int size, u32 *val)
{
	unsigned int v;

	if (bus->number != 0) return -EINVAL;
	switch (size) {
	case 1:
		pcic_read_config_dword(bus->number, devfn, where&~3, &v);
		*val = 0xff & (v >> (8*(where & 3)));
		return 0;
	case 2:
		if (where&1) return -EINVAL;
		pcic_read_config_dword(bus->number, devfn, where&~3, &v);
		*val = 0xffff & (v >> (8*(where & 3)));
		return 0;
	case 4:
		if (where&3) return -EINVAL;
		pcic_read_config_dword(bus->number, devfn, where&~3, val);
		return 0;
	}
	return -EINVAL;
}