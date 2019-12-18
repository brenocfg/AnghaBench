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
typedef  int /*<<< orphan*/  txt ;
struct wps_er_ap {int /*<<< orphan*/  location; int /*<<< orphan*/  addr; int /*<<< orphan*/  sid; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  inet_ntoa (int /*<<< orphan*/ ) ; 
 char* os_strstr (char*,char*) ; 
 int /*<<< orphan*/  uuid_bin2str (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ uuid_str2bin (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int wps_er_get_sid(struct wps_er_ap *ap, char *sid)
{
	char *pos;
	char txt[100];

	if (!sid) {
		wpa_printf(MSG_DEBUG, "WPS ER: No SID received from %s (%s)",
			   inet_ntoa(ap->addr), ap->location);
		return -1;
	}

	pos = os_strstr(sid, "uuid:");
	if (!pos) {
		wpa_printf(MSG_DEBUG, "WPS ER: Invalid SID received from "
			   "%s (%s): '%s'", inet_ntoa(ap->addr), ap->location,
			   sid);
		return -1;
	}

	pos += 5;
	if (uuid_str2bin(pos, ap->sid) < 0) {
		wpa_printf(MSG_DEBUG, "WPS ER: Invalid SID received from "
			   "%s (%s): '%s'", inet_ntoa(ap->addr), ap->location,
			   sid);
		return -1;
	}

	uuid_bin2str(ap->sid, txt, sizeof(txt));
	wpa_printf(MSG_DEBUG, "WPS ER: SID for subscription with %s (%s): %s",
		   inet_ntoa(ap->addr), ap->location, txt);

	return 0;
}