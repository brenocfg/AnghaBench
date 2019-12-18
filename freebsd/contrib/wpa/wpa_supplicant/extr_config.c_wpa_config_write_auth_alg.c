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
 int WPA_AUTH_ALG_LEAP ; 
 int WPA_AUTH_ALG_OPEN ; 
 int WPA_AUTH_ALG_SHARED ; 
 int /*<<< orphan*/  os_free (char*) ; 
 int os_snprintf (char*,int,char*,char*) ; 
 scalar_t__ os_snprintf_error (int,int) ; 
 char* os_zalloc (int) ; 

__attribute__((used)) static char * wpa_config_write_auth_alg(const struct parse_data *data,
					struct wpa_ssid *ssid)
{
	char *buf, *pos, *end;
	int ret;

	pos = buf = os_zalloc(30);
	if (buf == NULL)
		return NULL;
	end = buf + 30;

	if (ssid->auth_alg & WPA_AUTH_ALG_OPEN) {
		ret = os_snprintf(pos, end - pos, "%sOPEN",
				  pos == buf ? "" : " ");
		if (os_snprintf_error(end - pos, ret)) {
			end[-1] = '\0';
			return buf;
		}
		pos += ret;
	}

	if (ssid->auth_alg & WPA_AUTH_ALG_SHARED) {
		ret = os_snprintf(pos, end - pos, "%sSHARED",
				  pos == buf ? "" : " ");
		if (os_snprintf_error(end - pos, ret)) {
			end[-1] = '\0';
			return buf;
		}
		pos += ret;
	}

	if (ssid->auth_alg & WPA_AUTH_ALG_LEAP) {
		ret = os_snprintf(pos, end - pos, "%sLEAP",
				  pos == buf ? "" : " ");
		if (os_snprintf_error(end - pos, ret)) {
			end[-1] = '\0';
			return buf;
		}
		pos += ret;
	}

	if (pos == buf) {
		os_free(buf);
		buf = NULL;
	}

	return buf;
}