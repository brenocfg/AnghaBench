#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {scalar_t__ (* setup_device_regs ) (struct octeon_device*) ;int /*<<< orphan*/  (* disable_io_queues ) (struct octeon_device*) ;} ;
struct TYPE_3__ {int oq; int iq; } ;
struct octeon_device {scalar_t__ num_iqs; TYPE_2__ fn_list; TYPE_1__ io_qmask; } ;
struct lio {struct octeon_device* oct_dev; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int BIT_ULL (int) ; 
 int LIO_MAX_INSTR_QUEUES (struct octeon_device*) ; 
 int LIO_MAX_OUTPUT_QUEUES (struct octeon_device*) ; 
 struct lio* if_getsoftc (struct ifnet*) ; 
 int /*<<< orphan*/  lio_delete_droq (struct octeon_device*,int) ; 
 int /*<<< orphan*/  lio_delete_instr_queue (struct octeon_device*,int) ; 
 int /*<<< orphan*/  lio_dev_err (struct octeon_device*,char*) ; 
 scalar_t__ lio_send_queue_count_update (struct ifnet*,scalar_t__) ; 
 scalar_t__ lio_setup_io_queues (struct octeon_device*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ lio_wait_for_instr_fetch (struct octeon_device*) ; 
 scalar_t__ lio_wait_for_pending_requests (struct octeon_device*) ; 
 int /*<<< orphan*/  stub1 (struct octeon_device*) ; 
 scalar_t__ stub2 (struct octeon_device*) ; 

__attribute__((used)) static int
lio_reset_queues(struct ifnet *ifp, uint32_t num_qs)
{
	struct lio		*lio = if_getsoftc(ifp);
	struct octeon_device	*oct = lio->oct_dev;
	int	i, update = 0;

	if (lio_wait_for_pending_requests(oct))
		lio_dev_err(oct, "There were pending requests\n");

	if (lio_wait_for_instr_fetch(oct))
		lio_dev_err(oct, "IQ had pending instructions\n");


	/*
	 * Disable the input and output queues now. No more packets will
	 * arrive from Octeon.
	 */
	oct->fn_list.disable_io_queues(oct);

	if (num_qs != oct->num_iqs)
		update = 1;

	for (i = 0; i < LIO_MAX_OUTPUT_QUEUES(oct); i++) {
		if (!(oct->io_qmask.oq & BIT_ULL(i)))
			continue;

		lio_delete_droq(oct, i);
	}

	for (i = 0; i < LIO_MAX_INSTR_QUEUES(oct); i++) {
		if (!(oct->io_qmask.iq & BIT_ULL(i)))
			continue;

		lio_delete_instr_queue(oct, i);
	}

	if (oct->fn_list.setup_device_regs(oct)) {
		lio_dev_err(oct, "Failed to configure device registers\n");
		return (-1);
	}

	if (lio_setup_io_queues(oct, 0, num_qs, num_qs)) {
		lio_dev_err(oct, "IO queues initialization failed\n");
		return (-1);
	}

	if (update && lio_send_queue_count_update(ifp, num_qs))
		return (-1);

	return (0);
}