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
struct hostapd_sta_wpa_psk_short {struct hostapd_sta_wpa_psk_short* next; scalar_t__ ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (struct hostapd_sta_wpa_psk_short*) ; 

void hostapd_free_psk_list(struct hostapd_sta_wpa_psk_short *psk)
{
	if (psk && psk->ref) {
		/* This will be freed when the last reference is dropped. */
		psk->ref--;
		return;
	}

	while (psk) {
		struct hostapd_sta_wpa_psk_short *prev = psk;
		psk = psk->next;
		os_free(prev);
	}
}