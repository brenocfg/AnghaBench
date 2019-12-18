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
typedef  int /*<<< orphan*/  u32 ;
struct wpa_supplicant {TYPE_1__* global; } ;
struct TYPE_2__ {int /*<<< orphan*/  p2p; } ;

/* Variables and functions */
 int p2p_service_del_asp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpas_p2p_sd_service_update (struct wpa_supplicant*) ; 

int wpas_p2p_service_del_asp(struct wpa_supplicant *wpa_s, u32 adv_id)
{
	int ret;

	ret = p2p_service_del_asp(wpa_s->global->p2p, adv_id);
	if (ret == 0)
		wpas_p2p_sd_service_update(wpa_s);
	return ret;
}