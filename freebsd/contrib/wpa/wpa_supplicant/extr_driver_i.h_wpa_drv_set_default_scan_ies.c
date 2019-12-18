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
typedef  int /*<<< orphan*/  u8 ;
struct wpa_supplicant {int /*<<< orphan*/  drv_priv; TYPE_1__* driver; } ;
struct TYPE_2__ {int (* set_default_scan_ies ) (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static inline int wpa_drv_set_default_scan_ies(struct wpa_supplicant *wpa_s,
					       const u8 *ies, size_t len)
{
	if (!wpa_s->driver->set_default_scan_ies)
		return -1;
	return wpa_s->driver->set_default_scan_ies(wpa_s->drv_priv, ies, len);
}