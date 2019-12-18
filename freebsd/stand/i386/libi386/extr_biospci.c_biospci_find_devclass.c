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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int eax; int esi; int /*<<< orphan*/  ebx; int /*<<< orphan*/  efl; int /*<<< orphan*/  ecx; int /*<<< orphan*/  addr; int /*<<< orphan*/  ctl; } ;

/* Variables and functions */
 int FIND_PCI_CLASS_CODE ; 
 int /*<<< orphan*/  PCI_INT ; 
 scalar_t__ V86_CY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V86_FLAGS ; 
 TYPE_1__ v86 ; 
 int /*<<< orphan*/  v86int () ; 

int
biospci_find_devclass(uint32_t class, int index, uint32_t *locator)
{
	v86.ctl = V86_FLAGS;
	v86.addr = PCI_INT;
	v86.eax = FIND_PCI_CLASS_CODE;
	v86.ecx = class;
	v86.esi = index;
	v86int();

	 /* error */
	if (V86_CY(v86.efl) || (v86.eax & 0xff00))
		return (-1);

	*locator = v86.ebx;
	return (0);
}