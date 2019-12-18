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
struct ipw_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  IEEE80211_NWID_LEN ; 
 int /*<<< orphan*/  IPW_CMD_SET_ESSID ; 
 int /*<<< orphan*/  ieee80211_print_essid (void*,size_t) ; 
 int ipw_cmd (struct ipw_softc*,int /*<<< orphan*/ ,void*,size_t) ; 
 scalar_t__ ipw_debug ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
ipw_setssid(struct ipw_softc *sc, void *ssid, size_t ssidlen)
{
	if (ssidlen == 0) {
		/*
		 * A bug in the firmware breaks the ``don't associate''
		 * bit in the scan options command.  To compensate for
		 * this install a bogus ssid when no ssid is specified
		 * so the firmware won't try to associate.
		 */
		DPRINTF(("Setting bogus ESSID to WAR firmware bug\n"));
		return ipw_cmd(sc, IPW_CMD_SET_ESSID,
			"\x18\x19\x20\x21\x22\x23\x24\x25\x26\x27"
			"\x28\x29\x2a\x2b\x2c\x2d\x2e\x2f\x30\x31"
			"\x32\x33\x34\x35\x36\x37\x38\x39\x3a\x3b"
			"\x3c\x3d", IEEE80211_NWID_LEN);
	} else {
#ifdef IPW_DEBUG
		if (ipw_debug > 0) {
			printf("Setting ESSID to ");
			ieee80211_print_essid(ssid, ssidlen);
			printf("\n");
		}
#endif
		return ipw_cmd(sc, IPW_CMD_SET_ESSID, ssid, ssidlen);
	}
}