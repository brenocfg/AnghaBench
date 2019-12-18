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
typedef  int uint32_t ;
struct TYPE_2__ {int eax; int edx; int ecx; int esi; int ebx; int /*<<< orphan*/  efl; int /*<<< orphan*/  addr; int /*<<< orphan*/  ctl; } ;

/* Variables and functions */
 int FIND_PCI_DEVICE ; 
 int /*<<< orphan*/  PCI_INT ; 
 scalar_t__ V86_CY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V86_FLAGS ; 
 TYPE_1__ v86 ; 
 int /*<<< orphan*/  v86int () ; 

__attribute__((used)) static int
biospci_find_device(uint32_t devid, int index, uint32_t *locator)
{
	v86.ctl = V86_FLAGS;
	v86.addr = PCI_INT;
	v86.eax = FIND_PCI_DEVICE;
	v86.edx = devid & 0xffff;		/* EDX - Vendor ID */
	v86.ecx = (devid >> 16) & 0xffff;	/* ECX - Device ID */
	v86.esi = index;
	v86int();

	 /* error */
	if (V86_CY(v86.efl) || (v86.eax & 0xff00))
		return (-1);

	*locator = v86.ebx;
	return (0);
}