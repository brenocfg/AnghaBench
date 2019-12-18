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
struct wpa_ssid {int /*<<< orphan*/  bssid; int /*<<< orphan*/  bssid_set; } ;
struct parse_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC2STR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACSTR ; 
 int /*<<< orphan*/  os_free (char*) ; 
 char* os_malloc (int) ; 
 int os_snprintf (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ os_snprintf_error (int,int) ; 

__attribute__((used)) static char * wpa_config_write_bssid(const struct parse_data *data,
				     struct wpa_ssid *ssid)
{
	char *value;
	int res;

	if (!ssid->bssid_set)
		return NULL;

	value = os_malloc(20);
	if (value == NULL)
		return NULL;
	res = os_snprintf(value, 20, MACSTR, MAC2STR(ssid->bssid));
	if (os_snprintf_error(20, res)) {
		os_free(value);
		return NULL;
	}
	value[20 - 1] = '\0';
	return value;
}