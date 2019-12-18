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
struct evdev_dev {int* ev_rep; scalar_t__ ev_report_size; int /*<<< orphan*/ * ev_absinfo; int /*<<< orphan*/  ev_abs_flags; int /*<<< orphan*/  ev_mtx; int /*<<< orphan*/  ev_rep_callout; int /*<<< orphan*/  ev_flags; int /*<<< orphan*/  ev_clients; int /*<<< orphan*/  ev_serial; int /*<<< orphan*/  ev_name; int /*<<< orphan*/  ev_shortname; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_SLOT ; 
 int /*<<< orphan*/  EVDEV_FLAG_SOFTREPEAT ; 
 int /*<<< orphan*/  EV_REP ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 scalar_t__ MAXIMAL_MT_SLOT (struct evdev_dev*) ; 
 size_t REP_DELAY ; 
 size_t REP_PERIOD ; 
 scalar_t__ bit_test (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugf (struct evdev_dev*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int evdev_cdev_create (struct evdev_dev*) ; 
 int /*<<< orphan*/  evdev_estimate_report_size (struct evdev_dev*) ; 
 scalar_t__ evdev_event_supported (struct evdev_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evdev_mt_init (struct evdev_dev*) ; 
 int evdev_set_report_size (struct evdev_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evdev_sysctl_create (struct evdev_dev*) ; 

__attribute__((used)) static int
evdev_register_common(struct evdev_dev *evdev)
{
	int ret;

	debugf(evdev, "%s: registered evdev provider: %s <%s>\n",
	    evdev->ev_shortname, evdev->ev_name, evdev->ev_serial);

	/* Initialize internal structures */
	LIST_INIT(&evdev->ev_clients);

	if (evdev_event_supported(evdev, EV_REP) &&
	    bit_test(evdev->ev_flags, EVDEV_FLAG_SOFTREPEAT)) {
		/* Initialize callout */
		callout_init_mtx(&evdev->ev_rep_callout, &evdev->ev_mtx, 0);

		if (evdev->ev_rep[REP_DELAY] == 0 &&
		    evdev->ev_rep[REP_PERIOD] == 0) {
			/* Supply default values */
			evdev->ev_rep[REP_DELAY] = 250;
			evdev->ev_rep[REP_PERIOD] = 33;
		}
	}

	/* Initialize multitouch protocol type B states */
	if (bit_test(evdev->ev_abs_flags, ABS_MT_SLOT) &&
	    evdev->ev_absinfo != NULL && MAXIMAL_MT_SLOT(evdev) > 0)
		evdev_mt_init(evdev);

	/* Estimate maximum report size */
	if (evdev->ev_report_size == 0) {
		ret = evdev_set_report_size(evdev,
		    evdev_estimate_report_size(evdev));
		if (ret != 0)
			goto bail_out;
	}

	/* Create char device node */
	ret = evdev_cdev_create(evdev);
	if (ret != 0)
		goto bail_out;

	/* Create sysctls (for device enumeration without /dev/input access rights) */
	evdev_sysctl_create(evdev);

bail_out:
	return (ret);
}