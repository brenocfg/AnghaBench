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
struct wpa_supplicant {TYPE_1__* current_ssid; } ;
struct TYPE_2__ {scalar_t__ mode; scalar_t__ p2p_group; } ;

/* Variables and functions */
 scalar_t__ WPAS_MODE_INFRA ; 

__attribute__((used)) static int wpas_p2p_is_client(struct wpa_supplicant *wpa_s)
{
	if (wpa_s->current_ssid == NULL) {
		/*
		 * current_ssid can be cleared when P2P client interface gets
		 * disconnected, so assume this interface was used as P2P
		 * client.
		 */
		return 1;
	}
	return wpa_s->current_ssid->p2p_group &&
		wpa_s->current_ssid->mode == WPAS_MODE_INFRA;
}