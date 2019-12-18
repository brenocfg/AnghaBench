#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wpa_supplicant {int /*<<< orphan*/  p2p_group; TYPE_1__* conf; struct wpa_supplicant* next; TYPE_2__* global; } ;
struct wpa_ssid {scalar_t__ mode; scalar_t__ p2p_group; int /*<<< orphan*/  disabled; struct wpa_ssid* next; } ;
struct TYPE_4__ {struct wpa_supplicant* ifaces; } ;
struct TYPE_3__ {struct wpa_ssid* ssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ WPAS_MODE_P2P_GO ; 
 scalar_t__ p2p_get_group_num_members (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,struct wpa_supplicant*,struct wpa_ssid*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static unsigned int p2p_group_go_member_count(struct wpa_supplicant *wpa_s)
{
	unsigned int count = 0;
	struct wpa_ssid *s;

	for (wpa_s = wpa_s->global->ifaces; wpa_s; wpa_s = wpa_s->next) {
		for (s = wpa_s->conf->ssid; s; s = s->next) {
			wpa_printf(MSG_DEBUG,
				   "P2P: sup:%p ssid:%p disabled:%d p2p:%d mode:%d",
				   wpa_s, s, s->disabled, s->p2p_group,
				   s->mode);
			if (!s->disabled && s->p2p_group &&
			    s->mode == WPAS_MODE_P2P_GO) {
				count += p2p_get_group_num_members(
					wpa_s->p2p_group);
			}
		}
	}

	return count;
}