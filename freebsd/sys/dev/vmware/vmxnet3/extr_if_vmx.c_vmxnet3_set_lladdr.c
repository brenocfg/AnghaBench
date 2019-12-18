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
typedef  int uint32_t ;
struct vmxnet3_softc {int* vmx_lladdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMXNET3_BAR1_MACH ; 
 int /*<<< orphan*/  VMXNET3_BAR1_MACL ; 
 int /*<<< orphan*/  vmxnet3_write_bar1 (struct vmxnet3_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
vmxnet3_set_lladdr(struct vmxnet3_softc *sc)
{
	uint32_t ml, mh;

	ml  = sc->vmx_lladdr[0];
	ml |= sc->vmx_lladdr[1] << 8;
	ml |= sc->vmx_lladdr[2] << 16;
	ml |= sc->vmx_lladdr[3] << 24;
	vmxnet3_write_bar1(sc, VMXNET3_BAR1_MACL, ml);

	mh  = sc->vmx_lladdr[4];
	mh |= sc->vmx_lladdr[5] << 8;
	vmxnet3_write_bar1(sc, VMXNET3_BAR1_MACH, mh);
}