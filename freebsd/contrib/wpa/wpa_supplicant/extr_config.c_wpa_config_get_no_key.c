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
struct wpa_ssid {int dummy; } ;
struct parse_data {char* (* writer ) (struct parse_data const*,struct wpa_ssid*) ;scalar_t__ key_data; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 size_t NUM_SSID_FIELDS ; 
 int /*<<< orphan*/  os_free (char*) ; 
 scalar_t__ os_strcmp (char const*,int /*<<< orphan*/ ) ; 
 char* os_strdup (char*) ; 
 struct parse_data* ssid_fields ; 
 int /*<<< orphan*/  str_clear_free (char*) ; 
 char* stub1 (struct parse_data const*,struct wpa_ssid*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

char * wpa_config_get_no_key(struct wpa_ssid *ssid, const char *var)
{
	size_t i;

	if (ssid == NULL || var == NULL)
		return NULL;

	for (i = 0; i < NUM_SSID_FIELDS; i++) {
		const struct parse_data *field = &ssid_fields[i];
		if (os_strcmp(var, field->name) == 0) {
			char *res = field->writer(field, ssid);
			if (field->key_data) {
				if (res && res[0]) {
					wpa_printf(MSG_DEBUG, "Do not allow "
						   "key_data field to be "
						   "exposed");
					str_clear_free(res);
					return os_strdup("*");
				}

				os_free(res);
				return NULL;
			}
			return res;
		}
	}

	return NULL;
}