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
struct wpa_supplicant {unsigned int p2p_group_common_freqs_num; int* p2p_group_common_freqs; } ;

/* Variables and functions */
 int /*<<< orphan*/  p2p_go_dump_common_freqs (struct wpa_supplicant*) ; 

__attribute__((used)) static int wpas_p2p_go_is_peer_freq(struct wpa_supplicant *wpa_s, int freq)
{
	unsigned int i;

	p2p_go_dump_common_freqs(wpa_s);

	/* assume no restrictions */
	if (!wpa_s->p2p_group_common_freqs_num)
		return 1;

	for (i = 0; i < wpa_s->p2p_group_common_freqs_num; i++) {
		if (wpa_s->p2p_group_common_freqs[i] == freq)
			return 1;
	}
	return 0;
}