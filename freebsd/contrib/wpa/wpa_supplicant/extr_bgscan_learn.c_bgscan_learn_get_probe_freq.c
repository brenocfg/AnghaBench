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
struct bgscan_learn_data {int* supp_freqs; int probe_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  in_array (int*,int) ; 
 int* os_realloc_array (int*,size_t,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int * bgscan_learn_get_probe_freq(struct bgscan_learn_data *data,
					 int *freqs, size_t count)
{
	int idx, *n;

	if (data->supp_freqs == NULL)
		return freqs;

	idx = data->probe_idx;
	do {
		if (!in_array(freqs, data->supp_freqs[idx])) {
			wpa_printf(MSG_DEBUG, "bgscan learn: Probe new freq "
				   "%u", data->supp_freqs[idx]);
			data->probe_idx = idx + 1;
			if (data->supp_freqs[data->probe_idx] == 0)
				data->probe_idx = 0;
			n = os_realloc_array(freqs, count + 2, sizeof(int));
			if (n == NULL)
				return freqs;
			freqs = n;
			freqs[count] = data->supp_freqs[idx];
			count++;
			freqs[count] = 0;
			break;
		}

		idx++;
		if (data->supp_freqs[idx] == 0)
			idx = 0;
	} while (idx != data->probe_idx);

	return freqs;
}