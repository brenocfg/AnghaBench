#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct stp_sstpi {int dummy; } ;
struct clock_sync_data {unsigned long long clock_delta; int in_sync; int /*<<< orphan*/  cpus; } ;
struct TYPE_3__ {int tmd; scalar_t__* todoff; } ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ READ_ONCE (int) ; 
 int /*<<< orphan*/  STP_OP_SYNC ; 
 int /*<<< orphan*/  __udelay (int) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int chsc_sstpc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long*) ; 
 int chsc_sstpi (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  clock_sync_global (unsigned long long) ; 
 int /*<<< orphan*/  clock_sync_local (unsigned long long) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  disable_sync_clock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  enable_sync_clock () ; 
 TYPE_1__ stp_info ; 
 int /*<<< orphan*/  stp_page ; 
 scalar_t__ xchg (int*,int) ; 

__attribute__((used)) static int stp_sync_clock(void *data)
{
	struct clock_sync_data *sync = data;
	unsigned long long clock_delta;
	static int first;
	int rc;

	enable_sync_clock();
	if (xchg(&first, 1) == 0) {
		/* Wait until all other cpus entered the sync function. */
		while (atomic_read(&sync->cpus) != 0)
			cpu_relax();
		rc = 0;
		if (stp_info.todoff[0] || stp_info.todoff[1] ||
		    stp_info.todoff[2] || stp_info.todoff[3] ||
		    stp_info.tmd != 2) {
			rc = chsc_sstpc(stp_page, STP_OP_SYNC, 0,
					&clock_delta);
			if (rc == 0) {
				sync->clock_delta = clock_delta;
				clock_sync_global(clock_delta);
				rc = chsc_sstpi(stp_page, &stp_info,
						sizeof(struct stp_sstpi));
				if (rc == 0 && stp_info.tmd != 2)
					rc = -EAGAIN;
			}
		}
		sync->in_sync = rc ? -EAGAIN : 1;
		xchg(&first, 0);
	} else {
		/* Slave */
		atomic_dec(&sync->cpus);
		/* Wait for in_sync to be set. */
		while (READ_ONCE(sync->in_sync) == 0)
			__udelay(1);
	}
	if (sync->in_sync != 1)
		/* Didn't work. Clear per-cpu in sync bit again. */
		disable_sync_clock(NULL);
	/* Apply clock delta to per-CPU fields of this CPU. */
	clock_sync_local(sync->clock_delta);

	return 0;
}