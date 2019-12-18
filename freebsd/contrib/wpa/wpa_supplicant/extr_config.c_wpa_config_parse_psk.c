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
struct wpa_ssid {char const* passphrase; int psk_set; int /*<<< orphan*/  psk; int /*<<< orphan*/ * ext_psk; } ;
struct parse_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int PMK_LEN ; 
 char const* dup_binstr (char const*,size_t) ; 
 scalar_t__ has_ctrl_char (int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ hexstr2bin (char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 scalar_t__ os_memcmp (char const*,char const*,size_t) ; 
 int /*<<< orphan*/ * os_strdup (char const*) ; 
 size_t os_strlen (char const*) ; 
 scalar_t__ os_strncmp (char const*,char*,int) ; 
 char* os_strrchr (char const*,char) ; 
 int /*<<< orphan*/  str_clear_free (char const*) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int,...) ; 

__attribute__((used)) static int wpa_config_parse_psk(const struct parse_data *data,
				struct wpa_ssid *ssid, int line,
				const char *value)
{
#ifdef CONFIG_EXT_PASSWORD
	if (os_strncmp(value, "ext:", 4) == 0) {
		str_clear_free(ssid->passphrase);
		ssid->passphrase = NULL;
		ssid->psk_set = 0;
		os_free(ssid->ext_psk);
		ssid->ext_psk = os_strdup(value + 4);
		if (ssid->ext_psk == NULL)
			return -1;
		wpa_printf(MSG_DEBUG, "PSK: External password '%s'",
			   ssid->ext_psk);
		return 0;
	}
#endif /* CONFIG_EXT_PASSWORD */

	if (*value == '"') {
#ifndef CONFIG_NO_PBKDF2
		const char *pos;
		size_t len;

		value++;
		pos = os_strrchr(value, '"');
		if (pos)
			len = pos - value;
		else
			len = os_strlen(value);
		if (len < 8 || len > 63) {
			wpa_printf(MSG_ERROR, "Line %d: Invalid passphrase "
				   "length %lu (expected: 8..63) '%s'.",
				   line, (unsigned long) len, value);
			return -1;
		}
		wpa_hexdump_ascii_key(MSG_MSGDUMP, "PSK (ASCII passphrase)",
				      (u8 *) value, len);
		if (has_ctrl_char((u8 *) value, len)) {
			wpa_printf(MSG_ERROR,
				   "Line %d: Invalid passphrase character",
				   line);
			return -1;
		}
		if (ssid->passphrase && os_strlen(ssid->passphrase) == len &&
		    os_memcmp(ssid->passphrase, value, len) == 0) {
			/* No change to the previously configured value */
			return 1;
		}
		ssid->psk_set = 0;
		str_clear_free(ssid->passphrase);
		ssid->passphrase = dup_binstr(value, len);
		if (ssid->passphrase == NULL)
			return -1;
		return 0;
#else /* CONFIG_NO_PBKDF2 */
		wpa_printf(MSG_ERROR, "Line %d: ASCII passphrase not "
			   "supported.", line);
		return -1;
#endif /* CONFIG_NO_PBKDF2 */
	}

	if (hexstr2bin(value, ssid->psk, PMK_LEN) ||
	    value[PMK_LEN * 2] != '\0') {
		wpa_printf(MSG_ERROR, "Line %d: Invalid PSK '%s'.",
			   line, value);
		return -1;
	}

	str_clear_free(ssid->passphrase);
	ssid->passphrase = NULL;

	ssid->psk_set = 1;
	wpa_hexdump_key(MSG_MSGDUMP, "PSK", ssid->psk, PMK_LEN);
	return 0;
}