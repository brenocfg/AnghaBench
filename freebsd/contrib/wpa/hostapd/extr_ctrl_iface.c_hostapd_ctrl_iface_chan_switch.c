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
struct hostapd_iface {unsigned int num_bss; int /*<<< orphan*/ * bss; } ;
struct TYPE_2__ {int /*<<< orphan*/  vht_enabled; } ;
struct csa_settings {TYPE_1__ freq_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  hostapd_chan_switch_vht_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int hostapd_parse_csa_settings (char*,struct csa_settings*) ; 
 int hostapd_switch_channel (int /*<<< orphan*/ ,struct csa_settings*) ; 

__attribute__((used)) static int hostapd_ctrl_iface_chan_switch(struct hostapd_iface *iface,
					  char *pos)
{
#ifdef NEED_AP_MLME
	struct csa_settings settings;
	int ret;
	unsigned int i;

	ret = hostapd_parse_csa_settings(pos, &settings);
	if (ret)
		return ret;

	for (i = 0; i < iface->num_bss; i++) {

		/* Save CHAN_SWITCH VHT config */
		hostapd_chan_switch_vht_config(
			iface->bss[i], settings.freq_params.vht_enabled);

		ret = hostapd_switch_channel(iface->bss[i], &settings);
		if (ret) {
			/* FIX: What do we do if CSA fails in the middle of
			 * submitting multi-BSS CSA requests? */
			return ret;
		}
	}

	return 0;
#else /* NEED_AP_MLME */
	return -1;
#endif /* NEED_AP_MLME */
}