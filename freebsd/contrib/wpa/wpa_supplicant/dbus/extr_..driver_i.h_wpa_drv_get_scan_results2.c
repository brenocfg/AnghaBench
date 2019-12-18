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
struct wpa_supplicant {int /*<<< orphan*/  drv_priv; TYPE_1__* driver; } ;
struct wpa_scan_results {int dummy; } ;
struct TYPE_2__ {struct wpa_scan_results* (* get_scan_results2 ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 struct wpa_scan_results* stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct wpa_scan_results * wpa_drv_get_scan_results2(
	struct wpa_supplicant *wpa_s)
{
	if (wpa_s->driver->get_scan_results2)
		return wpa_s->driver->get_scan_results2(wpa_s->drv_priv);
	return NULL;
}