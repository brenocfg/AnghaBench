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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct wpa_supplicant {TYPE_1__* global; } ;
struct TYPE_2__ {int /*<<< orphan*/  p2p; } ;

/* Variables and functions */
 int p2p_service_add_asp (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  wpas_p2p_sd_service_update (struct wpa_supplicant*) ; 

int wpas_p2p_service_add_asp(struct wpa_supplicant *wpa_s,
			     int auto_accept, u32 adv_id,
			     const char *adv_str, u8 svc_state,
			     u16 config_methods, const char *svc_info,
			     const u8 *cpt_priority)
{
	int ret;

	ret = p2p_service_add_asp(wpa_s->global->p2p, auto_accept, adv_id,
				  adv_str, svc_state, config_methods,
				  svc_info, cpt_priority);
	if (ret == 0)
		wpas_p2p_sd_service_update(wpa_s);
	return ret;
}