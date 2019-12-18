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
struct wpa_ssid {int group_cipher; } ;
struct parse_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int WPA_ALLOWED_GROUP_CIPHERS ; 
 int WPA_CIPHER_WEP104 ; 
 int WPA_CIPHER_WEP40 ; 
 int wpa_config_parse_cipher (int,char const*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int,...) ; 

__attribute__((used)) static int wpa_config_parse_group(const struct parse_data *data,
				  struct wpa_ssid *ssid, int line,
				  const char *value)
{
	int val;
	val = wpa_config_parse_cipher(line, value);
	if (val == -1)
		return -1;

	/*
	 * Backwards compatibility - filter out WEP ciphers that were previously
	 * allowed.
	 */
	val &= ~(WPA_CIPHER_WEP104 | WPA_CIPHER_WEP40);

	if (val & ~WPA_ALLOWED_GROUP_CIPHERS) {
		wpa_printf(MSG_ERROR, "Line %d: not allowed group cipher "
			   "(0x%x).", line, val);
		return -1;
	}

	if (ssid->group_cipher == val)
		return 1;
	wpa_printf(MSG_MSGDUMP, "group: 0x%x", val);
	ssid->group_cipher = val;
	return 0;
}