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
struct vmbus_softc {int dummy; } ;
struct vmbus_channel {int ch_id; int /*<<< orphan*/  ch_cpuid; } ;

/* Variables and functions */
 int VMBUS_EVTFLAG_LEN ; 
 int* VMBUS_PCPU_PTR (struct vmbus_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_cmpset_int (int volatile*,int,int) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  event_flags_cnt ; 
 int /*<<< orphan*/  vmbus_chan_printf (struct vmbus_channel const*,char*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
vmbus_chan_update_evtflagcnt(struct vmbus_softc *sc,
    const struct vmbus_channel *chan)
{
	volatile int *flag_cnt_ptr;
	int flag_cnt;

	flag_cnt = (chan->ch_id / VMBUS_EVTFLAG_LEN) + 1;
	flag_cnt_ptr = VMBUS_PCPU_PTR(sc, event_flags_cnt, chan->ch_cpuid);

	for (;;) {
		int old_flag_cnt;

		old_flag_cnt = *flag_cnt_ptr;
		if (old_flag_cnt >= flag_cnt)
			break;
		if (atomic_cmpset_int(flag_cnt_ptr, old_flag_cnt, flag_cnt)) {
			if (bootverbose) {
				vmbus_chan_printf(chan,
				    "chan%u update cpu%d flag_cnt to %d\n",
				    chan->ch_id, chan->ch_cpuid, flag_cnt);
			}
			break;
		}
	}
}