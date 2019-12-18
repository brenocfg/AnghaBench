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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int PCI_RID2BUS (int /*<<< orphan*/ ) ; 
 int PCI_RID2FUNC (int /*<<< orphan*/ ) ; 
 int PCI_RID2SLOT (int /*<<< orphan*/ ) ; 

void
pcib_decode_rid(device_t pcib, uint16_t rid, int *bus, int *slot,
    int *func)
{

	*bus = PCI_RID2BUS(rid);
	*slot = PCI_RID2SLOT(rid);
	*func = PCI_RID2FUNC(rid);
}