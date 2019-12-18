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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct pci_bus {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inw (int /*<<< orphan*/ ) ; 

int pci_legacy_read(struct pci_bus *bus, u16 port, u32 *val, u8 size)
{
	int ret = size;

	switch (size) {
	case 1:
		*val = inb(port);
		break;
	case 2:
		*val = inw(port);
		break;
	case 4:
		*val = inl(port);
		break;
	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}