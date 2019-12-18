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
struct sta_info {int /*<<< orphan*/  assoc_ie_taxonomy; int /*<<< orphan*/  probe_ie_taxonomy; } ;
struct hostapd_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ie_to_string (char*,int,int /*<<< orphan*/ ) ; 
 int os_snprintf (char*,int,char*) ; 
 scalar_t__ os_snprintf_error (int,int) ; 
 char* os_strchr (char*,char) ; 

int retrieve_sta_taxonomy(const struct hostapd_data *hapd,
			  struct sta_info *sta, char *buf, size_t buflen)
{
	int ret;
	char *pos, *end;

	if (!sta->probe_ie_taxonomy || !sta->assoc_ie_taxonomy)
		return 0;

	ret = os_snprintf(buf, buflen, "wifi4|probe:");
	if (os_snprintf_error(buflen, ret))
		return 0;
	pos = buf + ret;
	end = buf + buflen;

	ie_to_string(pos, end - pos, sta->probe_ie_taxonomy);
	pos = os_strchr(pos, '\0');
	if (pos >= end)
		return 0;
	ret = os_snprintf(pos, end - pos, "|assoc:");
	if (os_snprintf_error(end - pos, ret))
		return 0;
	pos += ret;
	ie_to_string(pos, end - pos, sta->assoc_ie_taxonomy);
	pos = os_strchr(pos, '\0');
	return pos - buf;
}