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
struct wpa_ssid {int bssid_hint_set; int /*<<< orphan*/  bssid_hint; } ;
struct parse_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 scalar_t__ hwaddr_aton (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ os_strcmp (char const*,char*) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int wpa_config_parse_bssid_hint(const struct parse_data *data,
				       struct wpa_ssid *ssid, int line,
				       const char *value)
{
	if (value[0] == '\0' || os_strcmp(value, "\"\"") == 0 ||
	    os_strcmp(value, "any") == 0) {
		ssid->bssid_hint_set = 0;
		wpa_printf(MSG_MSGDUMP, "BSSID hint any");
		return 0;
	}
	if (hwaddr_aton(value, ssid->bssid_hint)) {
		wpa_printf(MSG_ERROR, "Line %d: Invalid BSSID hint '%s'.",
			   line, value);
		return -1;
	}
	ssid->bssid_hint_set = 1;
	wpa_hexdump(MSG_MSGDUMP, "BSSID hint", ssid->bssid_hint, ETH_ALEN);
	return 0;
}