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
struct assoc_info {int resp_ies_len; int beacon_ies_len; int /*<<< orphan*/  const* beacon_ies; int /*<<< orphan*/  const* resp_ies; } ;
union wpa_event_data {struct assoc_info assoc_info; } ;
typedef  int /*<<< orphan*/  u8 ;
struct wpa_supplicant {int /*<<< orphan*/ * received_mb_ies; struct wpa_bss* current_bss; } ;
struct wpa_bss {int ie_len; int beacon_ie_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpas_fst_update_mbie (struct wpa_supplicant*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void wpas_fst_update_mb_assoc(struct wpa_supplicant *wpa_s,
				     union wpa_event_data *data)
{
#ifdef CONFIG_FST
	struct assoc_info *ai = data ? &data->assoc_info : NULL;
	struct wpa_bss *bss = wpa_s->current_bss;
	const u8 *ieprb, *iebcn;

	wpabuf_free(wpa_s->received_mb_ies);
	wpa_s->received_mb_ies = NULL;

	if (ai &&
	    !wpas_fst_update_mbie(wpa_s, ai->resp_ies, ai->resp_ies_len)) {
		wpa_printf(MSG_DEBUG,
			   "FST: MB IEs updated from Association Response frame");
		return;
	}

	if (ai &&
	    !wpas_fst_update_mbie(wpa_s, ai->beacon_ies, ai->beacon_ies_len)) {
		wpa_printf(MSG_DEBUG,
			   "FST: MB IEs updated from association event Beacon IEs");
		return;
	}

	if (!bss)
		return;

	ieprb = (const u8 *) (bss + 1);
	iebcn = ieprb + bss->ie_len;

	if (!wpas_fst_update_mbie(wpa_s, ieprb, bss->ie_len))
		wpa_printf(MSG_DEBUG, "FST: MB IEs updated from bss IE");
	else if (!wpas_fst_update_mbie(wpa_s, iebcn, bss->beacon_ie_len))
		wpa_printf(MSG_DEBUG, "FST: MB IEs updated from bss beacon IE");
#endif /* CONFIG_FST */
}