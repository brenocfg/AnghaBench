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
struct wpa_supplicant {TYPE_1__ hw; int /*<<< orphan*/  current_bss; } ;
struct oper_class_map {int /*<<< orphan*/  mode; } ;
struct hostapd_hw_modes {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  WLAN_EID_COUNTRY ; 
 struct hostapd_hw_modes* get_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct oper_class_map* get_oper_class (char const*,int) ; 
 int /*<<< orphan*/  int_array_concat (int**,int*) ; 
 int /*<<< orphan*/  int_array_sort_unique (int*) ; 
 int /*<<< orphan*/  os_free (int*) ; 
 int* wpa_bss_get_ie (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int) ; 
 int* wpas_add_channels (struct oper_class_map const*,struct hostapd_hw_modes*,int,int*,int) ; 
 int* wpas_channel_report_freqs (struct wpa_supplicant*,int,char const*,int const*,size_t) ; 
 int* wpas_op_class_freqs (struct oper_class_map const*,struct hostapd_hw_modes*,int) ; 

__attribute__((used)) static int * wpas_beacon_request_freqs(struct wpa_supplicant *wpa_s,
				       u8 op_class, u8 chan, int active,
				       const u8 *subelems, size_t len)
{
	int *freqs = NULL, *ext_freqs = NULL;
	struct hostapd_hw_modes *mode;
	const char *country = NULL;
	const struct oper_class_map *op;
	const u8 *elem;

	if (!wpa_s->current_bss)
		return NULL;
	elem = wpa_bss_get_ie(wpa_s->current_bss, WLAN_EID_COUNTRY);
	if (elem && elem[1] >= 2)
		country = (const char *) (elem + 2);

	op = get_oper_class(country, op_class);
	if (!op) {
		wpa_printf(MSG_DEBUG,
			   "Beacon request: invalid operating class %d",
			   op_class);
		return NULL;
	}

	mode = get_mode(wpa_s->hw.modes, wpa_s->hw.num_modes, op->mode);
	if (!mode)
		return NULL;

	switch (chan) {
	case 0:
		freqs = wpas_op_class_freqs(op, mode, active);
		if (!freqs)
			return NULL;
		break;
	case 255:
		/* freqs will be added from AP channel subelements */
		break;
	default:
		freqs = wpas_add_channels(op, mode, active, &chan, 1);
		if (!freqs)
			return NULL;
		break;
	}

	ext_freqs = wpas_channel_report_freqs(wpa_s, active, country, subelems,
					      len);
	if (ext_freqs) {
		int_array_concat(&freqs, ext_freqs);
		os_free(ext_freqs);
		int_array_sort_unique(freqs);
	}

	return freqs;
}