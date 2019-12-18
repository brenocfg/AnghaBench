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
struct TYPE_2__ {int (* set_p2p_powersave ) (int /*<<< orphan*/ ,int,int,int) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static inline int wpa_drv_set_p2p_powersave(struct wpa_supplicant *wpa_s,
					    int legacy_ps, int opp_ps,
					    int ctwindow)
{
	if (!wpa_s->driver->set_p2p_powersave)
		return -1;
	return wpa_s->driver->set_p2p_powersave(wpa_s->drv_priv, legacy_ps,
						opp_ps, ctwindow);
}