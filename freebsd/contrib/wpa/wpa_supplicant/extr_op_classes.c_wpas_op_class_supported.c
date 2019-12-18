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
typedef  int u8 ;
struct TYPE_2__ {int /*<<< orphan*/  num_modes; int /*<<< orphan*/  modes; } ;
struct wpa_supplicant {TYPE_1__ hw; } ;
struct wpa_ssid {int* freq_list; scalar_t__ disable_vht; scalar_t__ disable_ht; } ;
struct oper_class_map {int op_class; int min_chan; int max_chan; int /*<<< orphan*/  bw; scalar_t__ inc; int /*<<< orphan*/  mode; } ;
struct hostapd_hw_modes {int dummy; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int*) ; 
 scalar_t__ NOT_ALLOWED ; 
 struct hostapd_hw_modes* get_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ verify_channel (struct hostapd_hw_modes*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wpas_op_class_supported(struct wpa_supplicant *wpa_s,
				   struct wpa_ssid *ssid,
				   const struct oper_class_map *op_class)
{
	int chan;
	size_t i;
	struct hostapd_hw_modes *mode;
	int found;
	int z;
	int freq2 = 0;
	int freq5 = 0;

	mode = get_mode(wpa_s->hw.modes, wpa_s->hw.num_modes, op_class->mode);
	if (!mode)
		return 0;

	/* If we are configured to disable certain things, take that into
	 * account here. */
	if (ssid->freq_list && ssid->freq_list[0]) {
		for (z = 0; ; z++) {
			int f = ssid->freq_list[z];

			if (f == 0)
				break; /* end of list */
			if (f > 4000 && f < 6000)
				freq5 = 1;
			else if (f > 2400 && f < 2500)
				freq2 = 1;
		}
	} else {
		/* No frequencies specified, can use anything hardware supports.
		 */
		freq2 = freq5 = 1;
	}

	if (op_class->op_class >= 115 && op_class->op_class <= 130 && !freq5)
		return 0;
	if (op_class->op_class >= 81 && op_class->op_class <= 84 && !freq2)
		return 0;

#ifdef CONFIG_HT_OVERRIDES
	if (ssid->disable_ht) {
		switch (op_class->op_class) {
		case 83:
		case 84:
		case 104:
		case 105:
		case 116:
		case 117:
		case 119:
		case 120:
		case 122:
		case 123:
		case 126:
		case 127:
		case 128:
		case 129:
		case 130:
			/* Disable >= 40 MHz channels if HT is disabled */
			return 0;
		}
	}
#endif /* CONFIG_HT_OVERRIDES */

#ifdef CONFIG_VHT_OVERRIDES
	if (ssid->disable_vht) {
		if (op_class->op_class >= 128 && op_class->op_class <= 130) {
			/* Disable >= 80 MHz channels if VHT is disabled */
			return 0;
		}
	}
#endif /* CONFIG_VHT_OVERRIDES */

	if (op_class->op_class == 128) {
		u8 channels[] = { 42, 58, 106, 122, 138, 155 };

		for (i = 0; i < ARRAY_SIZE(channels); i++) {
			if (verify_channel(mode, channels[i], op_class->bw) !=
			    NOT_ALLOWED)
				return 1;
		}

		return 0;
	}

	if (op_class->op_class == 129) {
		/* Check if either 160 MHz channels is allowed */
		return verify_channel(mode, 50, op_class->bw) != NOT_ALLOWED ||
			verify_channel(mode, 114, op_class->bw) != NOT_ALLOWED;
	}

	if (op_class->op_class == 130) {
		/* Need at least two non-contiguous 80 MHz segments */
		found = 0;

		if (verify_channel(mode, 42, op_class->bw) != NOT_ALLOWED ||
		    verify_channel(mode, 58, op_class->bw) != NOT_ALLOWED)
			found++;
		if (verify_channel(mode, 106, op_class->bw) != NOT_ALLOWED ||
		    verify_channel(mode, 122, op_class->bw) != NOT_ALLOWED ||
		    verify_channel(mode, 138, op_class->bw) != NOT_ALLOWED)
			found++;
		if (verify_channel(mode, 106, op_class->bw) != NOT_ALLOWED &&
		    verify_channel(mode, 138, op_class->bw) != NOT_ALLOWED)
			found++;
		if (verify_channel(mode, 155, op_class->bw) != NOT_ALLOWED)
			found++;

		if (found >= 2)
			return 1;

		return 0;
	}

	found = 0;
	for (chan = op_class->min_chan; chan <= op_class->max_chan;
	     chan += op_class->inc) {
		if (verify_channel(mode, chan, op_class->bw) != NOT_ALLOWED) {
			found = 1;
			break;
		}
	}

	return found;
}