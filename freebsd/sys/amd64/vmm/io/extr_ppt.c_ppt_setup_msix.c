#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint64_t ;
typedef  int uint32_t ;
struct vm {int dummy; } ;
struct TYPE_7__ {int num_msgs; int startrid; int msix_table_rid; int msix_pba_rid; int /*<<< orphan*/ ** res; int /*<<< orphan*/ ** cookie; TYPE_4__* arg; int /*<<< orphan*/ * msix_pba_res; int /*<<< orphan*/ * msix_table_res; } ;
struct pptdev {TYPE_3__ msix; int /*<<< orphan*/  dev; struct vm* vm; } ;
struct TYPE_5__ {int msix_table_bar; int msix_pba_bar; } ;
struct TYPE_6__ {TYPE_1__ msix; } ;
struct pci_devinfo {TYPE_2__ cfg; } ;
struct TYPE_8__ {void* msg_data; void* addr; struct pptdev* pptdev; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOSPC ; 
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_NET ; 
 int /*<<< orphan*/  M_PPTMSIX ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int PCIM_MSIX_VCTRL_MASK ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ **) ; 
 struct pci_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 void* malloc (size_t,int /*<<< orphan*/ ,int) ; 
 int pci_alloc_msix (int /*<<< orphan*/ ,int*) ; 
 int pci_msix_count (int /*<<< orphan*/ ) ; 
 struct pptdev* ppt_find (int,int,int) ; 
 int /*<<< orphan*/  ppt_teardown_msix (struct pptdev*) ; 
 int /*<<< orphan*/  ppt_teardown_msix_intr (struct pptdev*,int) ; 
 int /*<<< orphan*/  pptintr ; 

int
ppt_setup_msix(struct vm *vm, int vcpu, int bus, int slot, int func,
	       int idx, uint64_t addr, uint64_t msg, uint32_t vector_control)
{
	struct pptdev *ppt;
	struct pci_devinfo *dinfo;
	int numvec, alloced, rid, error;
	size_t res_size, cookie_size, arg_size;

	ppt = ppt_find(bus, slot, func);
	if (ppt == NULL)
		return (ENOENT);
	if (ppt->vm != vm)		/* Make sure we own this device */
		return (EBUSY);

	dinfo = device_get_ivars(ppt->dev);
	if (!dinfo) 
		return (ENXIO);

	/* 
	 * First-time configuration:
	 * 	Allocate the MSI-X table
	 *	Allocate the IRQ resources
	 *	Set up some variables in ppt->msix
	 */
	if (ppt->msix.num_msgs == 0) {
		numvec = pci_msix_count(ppt->dev);
		if (numvec <= 0)
			return (EINVAL);

		ppt->msix.startrid = 1;
		ppt->msix.num_msgs = numvec;

		res_size = numvec * sizeof(ppt->msix.res[0]);
		cookie_size = numvec * sizeof(ppt->msix.cookie[0]);
		arg_size = numvec * sizeof(ppt->msix.arg[0]);

		ppt->msix.res = malloc(res_size, M_PPTMSIX, M_WAITOK | M_ZERO);
		ppt->msix.cookie = malloc(cookie_size, M_PPTMSIX,
					  M_WAITOK | M_ZERO);
		ppt->msix.arg = malloc(arg_size, M_PPTMSIX, M_WAITOK | M_ZERO);

		rid = dinfo->cfg.msix.msix_table_bar;
		ppt->msix.msix_table_res = bus_alloc_resource_any(ppt->dev,
					       SYS_RES_MEMORY, &rid, RF_ACTIVE);

		if (ppt->msix.msix_table_res == NULL) {
			ppt_teardown_msix(ppt);
			return (ENOSPC);
		}
		ppt->msix.msix_table_rid = rid;

		if (dinfo->cfg.msix.msix_table_bar !=
		    dinfo->cfg.msix.msix_pba_bar) {
			rid = dinfo->cfg.msix.msix_pba_bar;
			ppt->msix.msix_pba_res = bus_alloc_resource_any(
			    ppt->dev, SYS_RES_MEMORY, &rid, RF_ACTIVE);

			if (ppt->msix.msix_pba_res == NULL) {
				ppt_teardown_msix(ppt);
				return (ENOSPC);
			}
			ppt->msix.msix_pba_rid = rid;
		}

		alloced = numvec;
		error = pci_alloc_msix(ppt->dev, &alloced);
		if (error || alloced != numvec) {
			ppt_teardown_msix(ppt);
			return (error == 0 ? ENOSPC: error);
		}
	}

	if ((vector_control & PCIM_MSIX_VCTRL_MASK) == 0) {
		/* Tear down the IRQ if it's already set up */
		ppt_teardown_msix_intr(ppt, idx);

		/* Allocate the IRQ resource */
		ppt->msix.cookie[idx] = NULL;
		rid = ppt->msix.startrid + idx;
		ppt->msix.res[idx] = bus_alloc_resource_any(ppt->dev, SYS_RES_IRQ,
							    &rid, RF_ACTIVE);
		if (ppt->msix.res[idx] == NULL)
			return (ENXIO);
	
		ppt->msix.arg[idx].pptdev = ppt;
		ppt->msix.arg[idx].addr = addr;
		ppt->msix.arg[idx].msg_data = msg;
	
		/* Setup the MSI-X interrupt */
		error = bus_setup_intr(ppt->dev, ppt->msix.res[idx],
				       INTR_TYPE_NET | INTR_MPSAFE,
				       pptintr, NULL, &ppt->msix.arg[idx],
				       &ppt->msix.cookie[idx]);
	
		if (error != 0) {
			bus_release_resource(ppt->dev, SYS_RES_IRQ, rid, ppt->msix.res[idx]);
			ppt->msix.cookie[idx] = NULL;
			ppt->msix.res[idx] = NULL;
			return (ENXIO);
		}
	} else {
		/* Masked, tear it down if it's already been set up */
		ppt_teardown_msix_intr(ppt, idx);
	}

	return (0);
}