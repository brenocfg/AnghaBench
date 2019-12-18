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
typedef  int /*<<< orphan*/  u16 ;
struct hostapd_hw_modes {int dummy; } ;
struct dpp_authentication {unsigned int num_freq; int /*<<< orphan*/ * freq; int /*<<< orphan*/  curr_freq; scalar_t__ freq_idx; TYPE_1__* peer_bi; } ;
typedef  int /*<<< orphan*/  freqs ;
struct TYPE_2__ {scalar_t__ num_freq; } ;

/* Variables and functions */
 int DPP_BOOTSTRAP_MAX_FREQ ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int dpp_channel_intersect (struct dpp_authentication*,struct hostapd_hw_modes*,int /*<<< orphan*/ ) ; 
 int dpp_channel_local_list (struct dpp_authentication*,struct hostapd_hw_modes*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freq_to_start (int /*<<< orphan*/ *,unsigned int,int) ; 
 int os_snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ os_snprintf_error (int,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int dpp_prepare_channel_list(struct dpp_authentication *auth,
				    struct hostapd_hw_modes *own_modes,
				    u16 num_modes)
{
	int res;
	char freqs[DPP_BOOTSTRAP_MAX_FREQ * 6 + 10], *pos, *end;
	unsigned int i;

	if (auth->peer_bi->num_freq > 0)
		res = dpp_channel_intersect(auth, own_modes, num_modes);
	else
		res = dpp_channel_local_list(auth, own_modes, num_modes);
	if (res < 0)
		return res;

	/* Prioritize 2.4 GHz channels 6, 1, 11 (in this order) to hit the most
	 * likely channels first. */
	freq_to_start(auth->freq, auth->num_freq, 2462);
	freq_to_start(auth->freq, auth->num_freq, 2412);
	freq_to_start(auth->freq, auth->num_freq, 2437);

	auth->freq_idx = 0;
	auth->curr_freq = auth->freq[0];

	pos = freqs;
	end = pos + sizeof(freqs);
	for (i = 0; i < auth->num_freq; i++) {
		res = os_snprintf(pos, end - pos, " %u", auth->freq[i]);
		if (os_snprintf_error(end - pos, res))
			break;
		pos += res;
	}
	*pos = '\0';
	wpa_printf(MSG_DEBUG, "DPP: Possible frequencies for initiating:%s",
		   freqs);

	return 0;
}