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
struct rsu_softc {int sc_extra_scan; int /*<<< orphan*/  sc_dev; scalar_t__ sc_active_scan; } ;
struct r92s_fw_cmd_sitesurvey {void* ssidlen; int /*<<< orphan*/  ssid; void* active; void* limit; } ;
struct ieee80211_scan_ssid {int len; int /*<<< orphan*/  ssid; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  R92S_CMD_SITE_SURVEY ; 
 int /*<<< orphan*/  RSU_ASSERT_LOCKED (struct rsu_softc*) ; 
 int RSU_DEBUG_FWCMD ; 
 int RSU_DEBUG_SCAN ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 void* htole32 (int) ; 
 int /*<<< orphan*/  ieee80211_print_essid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32toh (void*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct r92s_fw_cmd_sitesurvey*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int rsu_debug ; 
 int rsu_fw_cmd (struct rsu_softc*,int /*<<< orphan*/ ,struct r92s_fw_cmd_sitesurvey*,int) ; 

__attribute__((used)) static int
rsu_site_survey(struct rsu_softc *sc, struct ieee80211_scan_ssid *ssid)
{
	struct r92s_fw_cmd_sitesurvey cmd;

	RSU_ASSERT_LOCKED(sc);

	memset(&cmd, 0, sizeof(cmd));
	/* TODO: passive channels? */
	if (sc->sc_active_scan)
		cmd.active = htole32(1);
	cmd.limit = htole32(48);
	
	if (ssid != NULL) {
		sc->sc_extra_scan = 1;
		cmd.ssidlen = htole32(ssid->len);
		memcpy(cmd.ssid, ssid->ssid, ssid->len);
	}
#ifdef USB_DEBUG
	if (rsu_debug & (RSU_DEBUG_SCAN | RSU_DEBUG_FWCMD)) {
		device_printf(sc->sc_dev,
		    "sending site survey command, active %d",
		    le32toh(cmd.active));
		if (ssid != NULL) {
			printf(", ssid: ");
			ieee80211_print_essid(cmd.ssid, le32toh(cmd.ssidlen));
		}
		printf("\n");
	}
#endif
	return (rsu_fw_cmd(sc, R92S_CMD_SITE_SURVEY, &cmd, sizeof(cmd)));
}