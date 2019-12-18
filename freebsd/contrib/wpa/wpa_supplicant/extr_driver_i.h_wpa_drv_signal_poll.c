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
struct wpa_signal_info {int dummy; } ;
struct TYPE_2__ {int (* signal_poll ) (int /*<<< orphan*/ ,struct wpa_signal_info*) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,struct wpa_signal_info*) ; 

__attribute__((used)) static inline int wpa_drv_signal_poll(struct wpa_supplicant *wpa_s,
				      struct wpa_signal_info *si)
{
	if (wpa_s->driver->signal_poll)
		return wpa_s->driver->signal_poll(wpa_s->drv_priv, si);
	return -1;
}