#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wpa_supplicant {scalar_t__ test_failure; int /*<<< orphan*/  drv_priv; TYPE_1__* driver; } ;
struct wpa_driver_scan_params {int dummy; } ;
struct TYPE_2__ {int (* scan2 ) (int /*<<< orphan*/ ,struct wpa_driver_scan_params*) ;} ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ WPAS_TEST_FAILURE_SCAN_TRIGGER ; 
 int stub1 (int /*<<< orphan*/ ,struct wpa_driver_scan_params*) ; 

__attribute__((used)) static inline int wpa_drv_scan(struct wpa_supplicant *wpa_s,
			       struct wpa_driver_scan_params *params)
{
#ifdef CONFIG_TESTING_OPTIONS
	if (wpa_s->test_failure == WPAS_TEST_FAILURE_SCAN_TRIGGER)
		return -EBUSY;
#endif /* CONFIG_TESTING_OPTIONS */
	if (wpa_s->driver->scan2)
		return wpa_s->driver->scan2(wpa_s->drv_priv, params);
	return -1;
}