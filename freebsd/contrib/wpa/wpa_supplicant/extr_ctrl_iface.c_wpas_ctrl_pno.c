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
struct wpa_supplicant {int* manual_sched_scan_freqs; } ;

/* Variables and functions */
 scalar_t__ atoi (char*) ; 
 int* freq_range_to_channel_list (struct wpa_supplicant*,char*) ; 
 int /*<<< orphan*/  os_free (int*) ; 
 char* os_strchr (char*,char) ; 
 char* os_strstr (char*,char*) ; 
 int wpas_start_pno (struct wpa_supplicant*) ; 
 int wpas_stop_pno (struct wpa_supplicant*) ; 

__attribute__((used)) static int wpas_ctrl_pno(struct wpa_supplicant *wpa_s, char *cmd)
{
	char *params;
	char *pos;
	int *freqs = NULL;
	int ret;

	if (atoi(cmd)) {
		params = os_strchr(cmd, ' ');
		os_free(wpa_s->manual_sched_scan_freqs);
		if (params) {
			params++;
			pos = os_strstr(params, "freq=");
			if (pos)
				freqs = freq_range_to_channel_list(wpa_s,
								   pos + 5);
		}
		wpa_s->manual_sched_scan_freqs = freqs;
		ret = wpas_start_pno(wpa_s);
	} else {
		ret = wpas_stop_pno(wpa_s);
	}
	return ret;
}