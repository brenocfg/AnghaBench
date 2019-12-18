#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  (* soft_reset ) (struct octeon_device*) ;int /*<<< orphan*/  (* disable_interrupt ) (struct octeon_device*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* disable_io_queues ) (struct octeon_device*) ;} ;
struct TYPE_5__ {int oq; int iq; } ;
struct octeon_device {int /*<<< orphan*/  device; TYPE_3__ fn_list; int /*<<< orphan*/ ** instr_queue; TYPE_2__ io_qmask; int /*<<< orphan*/ ** droq; int /*<<< orphan*/ * msix_res; int /*<<< orphan*/  aux_vector; int /*<<< orphan*/ * tag; TYPE_1__* ioq_vector; int /*<<< orphan*/  num_msix_irqs; int /*<<< orphan*/  msix_on; int /*<<< orphan*/  status; int /*<<< orphan*/  app_mode; } ;
struct TYPE_4__ {int /*<<< orphan*/ * msix_res; int /*<<< orphan*/  vector; int /*<<< orphan*/ * tag; } ;

/* Variables and functions */
 int BIT_ULL (int) ; 
#define  LIO_DEV_BEGIN_STATE 143 
#define  LIO_DEV_CONSOLE_INIT_DONE 142 
#define  LIO_DEV_CORE_OK 141 
#define  LIO_DEV_DISPATCH_INIT_DONE 140 
#define  LIO_DEV_DROQ_INIT_DONE 139 
#define  LIO_DEV_HOST_OK 138 
#define  LIO_DEV_INSTR_QUEUE_INIT_DONE 137 
#define  LIO_DEV_INTR_SET_DONE 136 
#define  LIO_DEV_IN_RESET 135 
#define  LIO_DEV_IO_QUEUES_DONE 134 
#define  LIO_DEV_MSIX_ALLOC_VECTOR_DONE 133 
#define  LIO_DEV_PCI_ENABLE_DONE 132 
#define  LIO_DEV_PCI_MAP_DONE 131 
#define  LIO_DEV_RESP_LIST_INIT_DONE 130 
#define  LIO_DEV_RUNNING 129 
#define  LIO_DEV_SC_BUFF_POOL_INIT_DONE 128 
 int /*<<< orphan*/  LIO_DRV_INVALID_APP ; 
 int LIO_MAX_INSTR_QUEUES (struct octeon_device*) ; 
 int LIO_MAX_OUTPUT_QUEUES (struct octeon_device*) ; 
 int LIO_MAX_POSSIBLE_INSTR_QUEUES ; 
 int LIO_MAX_POSSIBLE_OUTPUT_QUEUES ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  OCTEON_ALL_INTR ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int atomic_load_acq_int (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_store_rel_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fw_type_is_none () ; 
 int /*<<< orphan*/  lio_delete_dispatch_list (struct octeon_device*) ; 
 int /*<<< orphan*/  lio_delete_droq (struct octeon_device*,int) ; 
 int /*<<< orphan*/  lio_delete_instr_queue (struct octeon_device*,int) ; 
 int /*<<< orphan*/  lio_delete_response_list (struct octeon_device*) ; 
 int lio_deregister_device (struct octeon_device*) ; 
 int /*<<< orphan*/  lio_dev_dbg (struct octeon_device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_dev_err (struct octeon_device*,char*) ; 
 int /*<<< orphan*/  lio_free_ioq_vector (struct octeon_device*) ; 
 int /*<<< orphan*/  lio_free_sc_buffer_pool (struct octeon_device*) ; 
 int /*<<< orphan*/  lio_get_state_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lio_mdelay (int) ; 
 int /*<<< orphan*/  lio_pci_flr (struct octeon_device*) ; 
 int /*<<< orphan*/  lio_remove_consoles (struct octeon_device*) ; 
 int /*<<< orphan*/  lio_sleep_timeout (int) ; 
 int /*<<< orphan*/  lio_unmap_pci_barx (struct octeon_device*,int) ; 
 int /*<<< orphan*/  lio_wait_for_instr_fetch (struct octeon_device*) ; 
 int /*<<< orphan*/  lio_wait_for_oq_pkts (struct octeon_device*) ; 
 int /*<<< orphan*/  lio_wait_for_pending_requests (struct octeon_device*) ; 
 int /*<<< orphan*/  pci_disable_busmaster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct octeon_device*) ; 
 int /*<<< orphan*/  stub2 (struct octeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct octeon_device*) ; 

__attribute__((used)) static void
lio_destroy_resources(struct octeon_device *oct)
{
	int i, refcount;

	switch (atomic_load_acq_int(&oct->status)) {
	case LIO_DEV_RUNNING:
	case LIO_DEV_CORE_OK:
		/* No more instructions will be forwarded. */
		atomic_store_rel_int(&oct->status, LIO_DEV_IN_RESET);

		oct->app_mode = LIO_DRV_INVALID_APP;
		lio_dev_dbg(oct, "Device state is now %s\n",
			    lio_get_state_string(&oct->status));

		lio_sleep_timeout(100);

		/* fallthrough */
	case LIO_DEV_HOST_OK:

		/* fallthrough */
	case LIO_DEV_CONSOLE_INIT_DONE:
		/* Remove any consoles */
		lio_remove_consoles(oct);

		/* fallthrough */
	case LIO_DEV_IO_QUEUES_DONE:
		if (lio_wait_for_pending_requests(oct))
			lio_dev_err(oct, "There were pending requests\n");

		if (lio_wait_for_instr_fetch(oct))
			lio_dev_err(oct, "IQ had pending instructions\n");

		/*
		 * Disable the input and output queues now. No more packets will
		 * arrive from Octeon, but we should wait for all packet
		 * processing to finish.
		 */
		oct->fn_list.disable_io_queues(oct);

		if (lio_wait_for_oq_pkts(oct))
			lio_dev_err(oct, "OQ had pending packets\n");

		/* fallthrough */
	case LIO_DEV_INTR_SET_DONE:
		/* Disable interrupts  */
		oct->fn_list.disable_interrupt(oct, OCTEON_ALL_INTR);

		if (oct->msix_on) {
			for (i = 0; i < oct->num_msix_irqs - 1; i++) {
				if (oct->ioq_vector[i].tag != NULL) {
					bus_teardown_intr(oct->device,
						  oct->ioq_vector[i].msix_res,
						      oct->ioq_vector[i].tag);
					oct->ioq_vector[i].tag = NULL;
				}
				if (oct->ioq_vector[i].msix_res != NULL) {
					bus_release_resource(oct->device,
						SYS_RES_IRQ,
						oct->ioq_vector[i].vector,
						oct->ioq_vector[i].msix_res);
					oct->ioq_vector[i].msix_res = NULL;
				}
			}
			/* non-iov vector's argument is oct struct */
			if (oct->tag != NULL) {
				bus_teardown_intr(oct->device, oct->msix_res,
						  oct->tag);
				oct->tag = NULL;
			}

			if (oct->msix_res != NULL) {
				bus_release_resource(oct->device, SYS_RES_IRQ,
						     oct->aux_vector,
						     oct->msix_res);
				oct->msix_res = NULL;
			}

			pci_release_msi(oct->device);
		}
		/* fallthrough */
	case LIO_DEV_IN_RESET:
	case LIO_DEV_DROQ_INIT_DONE:
		/* Wait for any pending operations */
		lio_mdelay(100);
		for (i = 0; i < LIO_MAX_OUTPUT_QUEUES(oct); i++) {
			if (!(oct->io_qmask.oq & BIT_ULL(i)))
				continue;
			lio_delete_droq(oct, i);
		}

		/* fallthrough */
	case LIO_DEV_RESP_LIST_INIT_DONE:
		for (i = 0; i < LIO_MAX_POSSIBLE_OUTPUT_QUEUES; i++) {
			if (oct->droq[i] != NULL) {
				free(oct->droq[i], M_DEVBUF);
				oct->droq[i] = NULL;
			}
		}
		lio_delete_response_list(oct);

		/* fallthrough */
	case LIO_DEV_INSTR_QUEUE_INIT_DONE:
		for (i = 0; i < LIO_MAX_INSTR_QUEUES(oct); i++) {
			if (!(oct->io_qmask.iq & BIT_ULL(i)))
				continue;

			lio_delete_instr_queue(oct, i);
		}

		/* fallthrough */
	case LIO_DEV_MSIX_ALLOC_VECTOR_DONE:
		for (i = 0; i < LIO_MAX_POSSIBLE_INSTR_QUEUES; i++) {
			if (oct->instr_queue[i] != NULL) {
				free(oct->instr_queue[i], M_DEVBUF);
				oct->instr_queue[i] = NULL;
			}
		}
		lio_free_ioq_vector(oct);

		/* fallthrough */
	case LIO_DEV_SC_BUFF_POOL_INIT_DONE:
		lio_free_sc_buffer_pool(oct);

		/* fallthrough */
	case LIO_DEV_DISPATCH_INIT_DONE:
		lio_delete_dispatch_list(oct);

		/* fallthrough */
	case LIO_DEV_PCI_MAP_DONE:
		refcount = lio_deregister_device(oct);

		if (fw_type_is_none())
			lio_pci_flr(oct);

		if (!refcount)
			oct->fn_list.soft_reset(oct);

		lio_unmap_pci_barx(oct, 0);
		lio_unmap_pci_barx(oct, 1);

		/* fallthrough */
	case LIO_DEV_PCI_ENABLE_DONE:
		/* Disable the device, releasing the PCI INT */
		pci_disable_busmaster(oct->device);

		/* fallthrough */
	case LIO_DEV_BEGIN_STATE:
		break;
	}	/* end switch (oct->status) */
}