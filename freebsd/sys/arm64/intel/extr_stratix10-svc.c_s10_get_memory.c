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
typedef  int /*<<< orphan*/  vmem_t ;
typedef  int /*<<< orphan*/  vmem_size_t ;
typedef  int /*<<< orphan*/  vmem_addr_t ;
struct s10_svc_softc {int /*<<< orphan*/ * vmem; int /*<<< orphan*/  dev; int /*<<< orphan*/  (* callfn ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct arm_smccc_res*) ;} ;
struct arm_smccc_res {scalar_t__ a0; int /*<<< orphan*/  a2; int /*<<< orphan*/  a1; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  INTEL_SIP_SMC_FPGA_CONFIG_GET_MEM ; 
 scalar_t__ INTEL_SIP_SMC_STATUS_OK ; 
 int M_BESTFIT ; 
 int M_WAITOK ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct arm_smccc_res*) ; 
 int /*<<< orphan*/  vmem_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vmem_create (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
s10_get_memory(struct s10_svc_softc *sc)
{
	struct arm_smccc_res res;
	vmem_addr_t addr;
	vmem_size_t size;
	vmem_t *vmem;

	sc->callfn(INTEL_SIP_SMC_FPGA_CONFIG_GET_MEM,
	    0, 0, 0, 0, 0, 0, 0, &res);
	if (res.a0 != INTEL_SIP_SMC_STATUS_OK)
		return (ENXIO);

	vmem = vmem_create("stratix10 vmem", 0, 0, PAGE_SIZE,
	    PAGE_SIZE, M_BESTFIT | M_WAITOK);
	if (vmem == NULL)
		return (ENXIO);

	addr = res.a1;
	size = res.a2;

	device_printf(sc->dev, "Shared memory address 0x%lx size 0x%lx\n",
	    addr, size);

	vmem_add(vmem, addr, size, 0);

	sc->vmem = vmem;

	return (0);
}