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
struct wpa_ssid {int proto; } ;
struct parse_data {int dummy; } ;

/* Variables and functions */
 int WPA_PROTO_OSEN ; 
 int WPA_PROTO_RSN ; 
 int WPA_PROTO_WPA ; 
 int /*<<< orphan*/  os_free (char*) ; 
 int os_snprintf (char*,int,char*,char*) ; 
 scalar_t__ os_snprintf_error (int,int) ; 
 char* os_zalloc (int) ; 

__attribute__((used)) static char * wpa_config_write_proto(const struct parse_data *data,
				     struct wpa_ssid *ssid)
{
	int ret;
	char *buf, *pos, *end;

	pos = buf = os_zalloc(20);
	if (buf == NULL)
		return NULL;
	end = buf + 20;

	if (ssid->proto & WPA_PROTO_WPA) {
		ret = os_snprintf(pos, end - pos, "%sWPA",
				  pos == buf ? "" : " ");
		if (os_snprintf_error(end - pos, ret))
			return buf;
		pos += ret;
	}

	if (ssid->proto & WPA_PROTO_RSN) {
		ret = os_snprintf(pos, end - pos, "%sRSN",
				  pos == buf ? "" : " ");
		if (os_snprintf_error(end - pos, ret))
			return buf;
		pos += ret;
	}

	if (ssid->proto & WPA_PROTO_OSEN) {
		ret = os_snprintf(pos, end - pos, "%sOSEN",
				  pos == buf ? "" : " ");
		if (os_snprintf_error(end - pos, ret))
			return buf;
		pos += ret;
	}

	if (pos == buf) {
		os_free(buf);
		buf = NULL;
	}

	return buf;
}