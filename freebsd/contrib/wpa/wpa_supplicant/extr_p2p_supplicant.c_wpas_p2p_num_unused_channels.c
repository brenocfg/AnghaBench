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
struct wpa_supplicant {int num_multichan_concurrent; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int get_shared_radio_freqs (struct wpa_supplicant*,int*,int) ; 
 int* os_calloc (int,int) ; 
 int /*<<< orphan*/  os_free (int*) ; 
 int /*<<< orphan*/  wpa_dbg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int wpas_p2p_num_unused_channels(struct wpa_supplicant *wpa_s)
{
	int *freqs;
	int num, unused;

	freqs = os_calloc(wpa_s->num_multichan_concurrent, sizeof(int));
	if (!freqs)
		return -1;

	num = get_shared_radio_freqs(wpa_s, freqs,
				     wpa_s->num_multichan_concurrent);
	os_free(freqs);

	unused = wpa_s->num_multichan_concurrent - num;
	wpa_dbg(wpa_s, MSG_DEBUG, "P2P: num_unused_channels: %d", unused);
	return unused;
}