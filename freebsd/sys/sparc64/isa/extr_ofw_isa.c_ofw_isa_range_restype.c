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
struct isa_ranges {int dummy; } ;

/* Variables and functions */
 int ISA_RANGE_PS (struct isa_ranges*) ; 
#define  OFW_PCI_CS_IO 129 
#define  OFW_PCI_CS_MEM32 128 
 int SYS_RES_IOPORT ; 
 int SYS_RES_MEMORY ; 
 int /*<<< orphan*/  panic (char*,int) ; 

int
ofw_isa_range_restype(struct isa_ranges *range)
{
	int ps = ISA_RANGE_PS(range);

	switch (ps) {
	case OFW_PCI_CS_IO:
		return (SYS_RES_IOPORT);
	case OFW_PCI_CS_MEM32:
		return (SYS_RES_MEMORY);
	default:
		panic("ofw_isa_range_restype: illegal space %x", ps);
	}

}