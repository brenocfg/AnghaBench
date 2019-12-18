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
 int /*<<< orphan*/  VMXNET3_CMD_GET_MACH ; 
 int /*<<< orphan*/  VMXNET3_CMD_GET_MACL ; 
 int vmxnet3_read_cmd (struct vmxnet3_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vmxnet3_get_lladdr(struct vmxnet3_softc *sc)
{
	uint32_t ml, mh;

	ml = vmxnet3_read_cmd(sc, VMXNET3_CMD_GET_MACL);
	mh = vmxnet3_read_cmd(sc, VMXNET3_CMD_GET_MACH);

	sc->vmx_lladdr[0] = ml;
	sc->vmx_lladdr[1] = ml >> 8;
	sc->vmx_lladdr[2] = ml >> 16;
	sc->vmx_lladdr[3] = ml >> 24;
	sc->vmx_lladdr[4] = mh;
	sc->vmx_lladdr[5] = mh >> 8;
}