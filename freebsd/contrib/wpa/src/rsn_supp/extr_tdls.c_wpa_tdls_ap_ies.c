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
typedef  int /*<<< orphan*/  u8 ;
struct wpa_sm {int /*<<< orphan*/  tdls_chan_switch_prohibited; int /*<<< orphan*/  tdls_prohibited; } ;
struct ieee802_11_elems {int ext_capab_len; int /*<<< orphan*/ * ext_capab; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ ParseFailed ; 
 scalar_t__ ieee802_11_parse_elems (int /*<<< orphan*/  const*,size_t,struct ieee802_11_elems*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  wpa_tdls_chan_switch_prohibited (struct ieee802_11_elems*) ; 
 int /*<<< orphan*/  wpa_tdls_prohibited (struct ieee802_11_elems*) ; 

void wpa_tdls_ap_ies(struct wpa_sm *sm, const u8 *ies, size_t len)
{
	struct ieee802_11_elems elems;

	sm->tdls_prohibited = 0;
	sm->tdls_chan_switch_prohibited = 0;

	if (ies == NULL ||
	    ieee802_11_parse_elems(ies, len, &elems, 0) == ParseFailed ||
	    elems.ext_capab == NULL || elems.ext_capab_len < 5)
		return;

	sm->tdls_prohibited = wpa_tdls_prohibited(&elems);
	wpa_printf(MSG_DEBUG, "TDLS: TDLS is %s in the target BSS",
		   sm->tdls_prohibited ? "prohibited" : "allowed");
	sm->tdls_chan_switch_prohibited =
		wpa_tdls_chan_switch_prohibited(&elems);
	wpa_printf(MSG_DEBUG, "TDLS: TDLS channel switch %s in the target BSS",
		   sm->tdls_chan_switch_prohibited ? "prohibited" : "allowed");
}