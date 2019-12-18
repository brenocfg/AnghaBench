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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int uint8_t ;
typedef  int uint64_t ;
struct vmbus_ic_softc {int /*<<< orphan*/  ic_dev; } ;
struct timespec {int tv_sec; int tv_nsec; } ;
typedef  int int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int HYPERV_TIMER_NS_FACTOR ; 
 int NANOSEC ; 
 int VMBUS_ICMSG_TS_BASE ; 
 int VMBUS_ICMSG_TS_FLAG_SAMPLE ; 
 int VMBUS_ICMSG_TS_FLAG_SYNC ; 
 scalar_t__ VMBUS_TIMESYNC_DORTT (struct vmbus_ic_softc*) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hyperv_tc64 () ; 
 int /*<<< orphan*/  kern_clock_settime (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  nanotime (struct timespec*) ; 
 int /*<<< orphan*/  vmbus_ts_ignore_sync ; 
 int vmbus_ts_sample_thresh ; 
 scalar_t__ vmbus_ts_sample_verbose ; 

__attribute__((used)) static void
vmbus_timesync(struct vmbus_ic_softc *sc, uint64_t hvtime, uint64_t sent_tc,
    uint8_t tsflags)
{
	struct timespec vm_ts;
	uint64_t hv_ns, vm_ns, rtt = 0;

	if (VMBUS_TIMESYNC_DORTT(sc))
		rtt = hyperv_tc64() - sent_tc;

	hv_ns = (hvtime - VMBUS_ICMSG_TS_BASE + rtt) * HYPERV_TIMER_NS_FACTOR;
	nanotime(&vm_ts);
	vm_ns = (vm_ts.tv_sec * NANOSEC) + vm_ts.tv_nsec;

	if ((tsflags & VMBUS_ICMSG_TS_FLAG_SYNC) && !vmbus_ts_ignore_sync) {
		struct timespec hv_ts;

		if (bootverbose) {
			device_printf(sc->ic_dev, "apply sync request, "
			    "hv: %ju, vm: %ju\n",
			    (uintmax_t)hv_ns, (uintmax_t)vm_ns);
		}
		hv_ts.tv_sec = hv_ns / NANOSEC;
		hv_ts.tv_nsec = hv_ns % NANOSEC;
		kern_clock_settime(curthread, CLOCK_REALTIME, &hv_ts);
		/* Done! */
		return;
	}

	if ((tsflags & VMBUS_ICMSG_TS_FLAG_SAMPLE) &&
	    vmbus_ts_sample_thresh >= 0) {
		int64_t diff;

		if (vmbus_ts_sample_verbose) {
			device_printf(sc->ic_dev, "sample request, "
			    "hv: %ju, vm: %ju\n",
			    (uintmax_t)hv_ns, (uintmax_t)vm_ns);
		}

		if (hv_ns > vm_ns)
			diff = hv_ns - vm_ns;
		else
			diff = vm_ns - hv_ns;
		/* nanosec -> millisec */
		diff /= 1000000;

		if (diff > vmbus_ts_sample_thresh) {
			struct timespec hv_ts;

			if (bootverbose) {
				device_printf(sc->ic_dev,
				    "apply sample request, hv: %ju, vm: %ju\n",
				    (uintmax_t)hv_ns, (uintmax_t)vm_ns);
			}
			hv_ts.tv_sec = hv_ns / NANOSEC;
			hv_ts.tv_nsec = hv_ns % NANOSEC;
			kern_clock_settime(curthread, CLOCK_REALTIME, &hv_ts);
		}
		/* Done */
		return;
	}
}