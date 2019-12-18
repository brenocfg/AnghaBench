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
struct TYPE_2__ {int /*<<< orphan*/  freqs; } ;
struct beacon_rep_data {TYPE_1__ scan_params; int /*<<< orphan*/  eids; } ;
struct wpa_supplicant {struct beacon_rep_data beacon_rep_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  bitfield_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct wpa_supplicant*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memset (struct beacon_rep_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpas_rrm_scan_timeout ; 

void wpas_clear_beacon_rep_data(struct wpa_supplicant *wpa_s)
{
	struct beacon_rep_data *data = &wpa_s->beacon_rep_data;

	eloop_cancel_timeout(wpas_rrm_scan_timeout, wpa_s, NULL);
	bitfield_free(data->eids);
	os_free(data->scan_params.freqs);
	os_memset(data, 0, sizeof(*data));
}