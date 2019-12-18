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
struct wpa_supplicant {TYPE_1__* global; } ;
struct TYPE_2__ {scalar_t__ p2p; } ;

/* Variables and functions */
 int /*<<< orphan*/  p2p_sd_service_update (scalar_t__) ; 

void wpas_p2p_sd_service_update(struct wpa_supplicant *wpa_s)
{
	if (wpa_s->global->p2p)
		p2p_sd_service_update(wpa_s->global->p2p);
}