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
typedef  int /*<<< orphan*/  u32 ;
struct wpa_supplicant {scalar_t__ wpa_state; int waiting_presence_resp; int /*<<< orphan*/  assoc_freq; int /*<<< orphan*/  own_addr; int /*<<< orphan*/  bssid; TYPE_2__* global; TYPE_1__* current_ssid; } ;
struct TYPE_4__ {int /*<<< orphan*/ * p2p; scalar_t__ p2p_disabled; } ;
struct TYPE_3__ {scalar_t__ mode; } ;

/* Variables and functions */
 scalar_t__ WPAS_MODE_INFRA ; 
 scalar_t__ WPA_ASSOCIATED ; 
 int p2p_presence_req (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int wpas_p2p_presence_req(struct wpa_supplicant *wpa_s, u32 duration1,
			  u32 interval1, u32 duration2, u32 interval2)
{
	int ret;

	if (wpa_s->global->p2p_disabled || wpa_s->global->p2p == NULL)
		return -1;

	if (wpa_s->wpa_state < WPA_ASSOCIATED ||
	    wpa_s->current_ssid == NULL ||
	    wpa_s->current_ssid->mode != WPAS_MODE_INFRA)
		return -1;

	ret = p2p_presence_req(wpa_s->global->p2p, wpa_s->bssid,
			       wpa_s->own_addr, wpa_s->assoc_freq,
			       duration1, interval1, duration2, interval2);
	if (ret == 0)
		wpa_s->waiting_presence_resp = 1;

	return ret;
}