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
struct wpa_driver_capa {int /*<<< orphan*/  flags; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  WPA_DRIVER_FLAGS_TDLS_EXTERNAL_SETUP ; 
 int /*<<< orphan*/  WPA_DRIVER_FLAGS_TDLS_SUPPORT ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void wiphy_info_tdls(struct wpa_driver_capa *capa, struct nlattr *tdls,
			    struct nlattr *ext_setup)
{
	if (tdls == NULL)
		return;

	wpa_printf(MSG_DEBUG, "nl80211: TDLS supported");
	capa->flags |= WPA_DRIVER_FLAGS_TDLS_SUPPORT;

	if (ext_setup) {
		wpa_printf(MSG_DEBUG, "nl80211: TDLS external setup");
		capa->flags |= WPA_DRIVER_FLAGS_TDLS_EXTERNAL_SETUP;
	}
}