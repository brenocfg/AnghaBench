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
typedef  int uint16_t ;
struct vmxnet3_softc {int* vmx_vlan_filter; } ;

/* Variables and functions */

__attribute__((used)) static void
vmxnet3_update_vlan_filter(struct vmxnet3_softc *sc, int add, uint16_t tag)
{
	int idx, bit;

	if (tag == 0 || tag > 4095)
		return;

	idx = (tag >> 5) & 0x7F;
	bit = tag & 0x1F;

	/* Update our private VLAN bitvector. */
	if (add)
		sc->vmx_vlan_filter[idx] |= (1 << bit);
	else
		sc->vmx_vlan_filter[idx] &= ~(1 << bit);
}