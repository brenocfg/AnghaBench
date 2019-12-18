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
struct wpa_ssid {int auth_alg; } ;
struct parse_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int WPA_AUTH_ALG_LEAP ; 
 int WPA_AUTH_ALG_OPEN ; 
 int WPA_AUTH_ALG_SHARED ; 
 int /*<<< orphan*/  os_free (char*) ; 
 scalar_t__ os_strcmp (char*,char*) ; 
 char* os_strdup (char const*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int,...) ; 

__attribute__((used)) static int wpa_config_parse_auth_alg(const struct parse_data *data,
				     struct wpa_ssid *ssid, int line,
				     const char *value)
{
	int val = 0, last, errors = 0;
	char *start, *end, *buf;

	buf = os_strdup(value);
	if (buf == NULL)
		return -1;
	start = buf;

	while (*start != '\0') {
		while (*start == ' ' || *start == '\t')
			start++;
		if (*start == '\0')
			break;
		end = start;
		while (*end != ' ' && *end != '\t' && *end != '\0')
			end++;
		last = *end == '\0';
		*end = '\0';
		if (os_strcmp(start, "OPEN") == 0)
			val |= WPA_AUTH_ALG_OPEN;
		else if (os_strcmp(start, "SHARED") == 0)
			val |= WPA_AUTH_ALG_SHARED;
		else if (os_strcmp(start, "LEAP") == 0)
			val |= WPA_AUTH_ALG_LEAP;
		else {
			wpa_printf(MSG_ERROR, "Line %d: invalid auth_alg '%s'",
				   line, start);
			errors++;
		}

		if (last)
			break;
		start = end + 1;
	}
	os_free(buf);

	if (val == 0) {
		wpa_printf(MSG_ERROR,
			   "Line %d: no auth_alg values configured.", line);
		errors++;
	}

	if (!errors && ssid->auth_alg == val)
		return 1;
	wpa_printf(MSG_MSGDUMP, "auth_alg: 0x%x", val);
	ssid->auth_alg = val;
	return errors ? -1 : 0;
}