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
struct TYPE_4__ {int iq; } ;
struct octeon_device {TYPE_1__** instr_queue; TYPE_2__ io_qmask; } ;
struct TYPE_3__ {int /*<<< orphan*/  instr_pending; } ;

/* Variables and functions */
 int BIT_ULL (int) ; 
 int LIO_MAX_INSTR_QUEUES (struct octeon_device*) ; 
 int /*<<< orphan*/  __lio_check_db_timeout (struct octeon_device*,int) ; 
 int atomic_load_acq_int (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lio_sleep_timeout (int) ; 

int
lio_wait_for_instr_fetch(struct octeon_device *oct)
{
	int	i, retry = 1000, pending, instr_cnt = 0;

	do {
		instr_cnt = 0;

		for (i = 0; i < LIO_MAX_INSTR_QUEUES(oct); i++) {
			if (!(oct->io_qmask.iq & BIT_ULL(i)))
				continue;
			pending = atomic_load_acq_int(
					&oct->instr_queue[i]->instr_pending);
			if (pending)
				__lio_check_db_timeout(oct, i);
			instr_cnt += pending;
		}

		if (instr_cnt == 0)
			break;

		lio_sleep_timeout(1);

	} while (retry-- && instr_cnt);

	return (instr_cnt);
}