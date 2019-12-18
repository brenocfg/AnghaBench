#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int next_neighbor_rep_token; scalar_t__ notify_neighbor_rep; scalar_t__ rrm_used; } ;
struct wpa_supplicant {TYPE_1__ rrm; } ;

/* Variables and functions */
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/  (*) (TYPE_1__*,int /*<<< orphan*/ *),TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpas_clear_beacon_rep_data (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpas_rrm_neighbor_rep_timeout_handler (TYPE_1__*,int /*<<< orphan*/ *) ; 

void wpas_rrm_reset(struct wpa_supplicant *wpa_s)
{
	wpa_s->rrm.rrm_used = 0;

	eloop_cancel_timeout(wpas_rrm_neighbor_rep_timeout_handler, &wpa_s->rrm,
			     NULL);
	if (wpa_s->rrm.notify_neighbor_rep)
		wpas_rrm_neighbor_rep_timeout_handler(&wpa_s->rrm, NULL);
	wpa_s->rrm.next_neighbor_rep_token = 1;
	wpas_clear_beacon_rep_data(wpa_s);
}