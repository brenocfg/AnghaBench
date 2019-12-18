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
struct wpa_used_freq_data {int freq; int flags; } ;
struct wpa_supplicant {TYPE_1__* global; } ;
struct TYPE_2__ {int /*<<< orphan*/  p2p; } ;

/* Variables and functions */
 int WPA_FREQ_USED_BY_INFRA_STATION ; 
 int WPA_FREQ_USED_BY_P2P_CLIENT ; 
 scalar_t__ p2p_supported_freq (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wpas_p2p_pick_best_used_freq(struct wpa_supplicant *wpa_s,
					struct wpa_used_freq_data *freqs,
					unsigned int num)
{
	unsigned int i, c;

	/* find a candidate freq that is supported by P2P */
	for (c = 0; c < num; c++)
		if (p2p_supported_freq(wpa_s->global->p2p, freqs[c].freq))
			break;

	if (c == num)
		return 0;

	/* once we have a candidate, try to find a 'better' one */
	for (i = c + 1; i < num; i++) {
		if (!p2p_supported_freq(wpa_s->global->p2p, freqs[i].freq))
			continue;

		/*
		 * 1. Infrastructure station interfaces have higher preference.
		 * 2. P2P Clients have higher preference.
		 * 3. All others.
		 */
		if (freqs[i].flags & WPA_FREQ_USED_BY_INFRA_STATION) {
			c = i;
			break;
		}

		if ((freqs[i].flags & WPA_FREQ_USED_BY_P2P_CLIENT))
			c = i;
	}
	return freqs[c].freq;
}