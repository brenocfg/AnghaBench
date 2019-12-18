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
struct wpa_used_freq_data {int freq; } ;
struct wpa_supplicant {int dummy; } ;

/* Variables and functions */
 int get_shared_radio_freqs_data (struct wpa_supplicant*,struct wpa_used_freq_data*,unsigned int) ; 
 struct wpa_used_freq_data* os_calloc (unsigned int,int) ; 
 int /*<<< orphan*/  os_free (struct wpa_used_freq_data*) ; 
 int /*<<< orphan*/  os_memset (int*,int /*<<< orphan*/ ,int) ; 

int get_shared_radio_freqs(struct wpa_supplicant *wpa_s,
			   int *freq_array, unsigned int len)
{
	struct wpa_used_freq_data *freqs_data;
	int num, i;

	os_memset(freq_array, 0, sizeof(int) * len);

	freqs_data = os_calloc(len, sizeof(struct wpa_used_freq_data));
	if (!freqs_data)
		return -1;

	num = get_shared_radio_freqs_data(wpa_s, freqs_data, len);
	for (i = 0; i < num; i++)
		freq_array[i] = freqs_data[i].freq;

	os_free(freqs_data);

	return num;
}