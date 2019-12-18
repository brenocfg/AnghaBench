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
struct wpa_used_freq_data {int /*<<< orphan*/  flags; int /*<<< orphan*/  freq; } ;
struct wpa_supplicant {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_dbg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*,unsigned int,char const*,...) ; 

void dump_freq_data(struct wpa_supplicant *wpa_s, const char *title,
		    struct wpa_used_freq_data *freqs_data,
		    unsigned int len)
{
	unsigned int i;

	wpa_dbg(wpa_s, MSG_DEBUG, "Shared frequencies (len=%u): %s",
		len, title);
	for (i = 0; i < len; i++) {
		struct wpa_used_freq_data *cur = &freqs_data[i];
		wpa_dbg(wpa_s, MSG_DEBUG, "freq[%u]: %d, flags=0x%X",
			i, cur->freq, cur->flags);
	}
}