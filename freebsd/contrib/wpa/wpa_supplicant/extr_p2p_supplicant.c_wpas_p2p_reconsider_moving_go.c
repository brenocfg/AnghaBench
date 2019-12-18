#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct wpa_used_freq_data {int dummy; } ;
struct wpa_supplicant {unsigned int num_multichan_concurrent; } ;

/* Variables and functions */
 int /*<<< orphan*/  WPAS_P2P_CHANNEL_UPDATE_ANY ; 
 unsigned int get_shared_radio_freqs_data (struct wpa_supplicant*,struct wpa_used_freq_data*,unsigned int) ; 
 struct wpa_used_freq_data* os_calloc (unsigned int,int) ; 
 int /*<<< orphan*/  os_free (struct wpa_used_freq_data*) ; 
 int /*<<< orphan*/  wpas_p2p_consider_moving_gos (struct wpa_supplicant*,struct wpa_used_freq_data*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wpas_p2p_reconsider_moving_go(void *eloop_ctx, void *timeout_ctx)
{
	struct wpa_supplicant *wpa_s = eloop_ctx;
	struct wpa_used_freq_data *freqs = NULL;
	unsigned int num = wpa_s->num_multichan_concurrent;

	freqs = os_calloc(num, sizeof(struct wpa_used_freq_data));
	if (!freqs)
		return;

	num = get_shared_radio_freqs_data(wpa_s, freqs, num);

	/* Previous attempt to move a GO was not possible -- try again. */
	wpas_p2p_consider_moving_gos(wpa_s, freqs, num,
				     WPAS_P2P_CHANNEL_UPDATE_ANY);

	os_free(freqs);
}