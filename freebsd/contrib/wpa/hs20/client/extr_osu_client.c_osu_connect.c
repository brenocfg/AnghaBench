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
struct wpa_ctrl {int dummy; } ;
struct hs20_osu_client {char* ifname; int no_reconnect; scalar_t__ osu_ssid; } ;
typedef  int /*<<< orphan*/  fname ;
typedef  int /*<<< orphan*/  dir ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int add_network (char const*) ; 
 int cmd_oma_dm_prov (struct hs20_osu_client*,char const*) ; 
 int cmd_prov (struct hs20_osu_client*,char const*) ; 
 int get_wpa_cli_event (struct wpa_ctrl*,char*,char*,int) ; 
 int /*<<< orphan*/ * getcwd (char*,int) ; 
 struct wpa_ctrl* open_wpa_mon (char const*) ; 
 int /*<<< orphan*/  os_snprintf (char*,int,char*,char*) ; 
 scalar_t__ os_strcmp (char const*,scalar_t__) ; 
 scalar_t__ os_strlen (char const*) ; 
 scalar_t__ set_network (char const*,int,char*,char*) ; 
 scalar_t__ set_network_quoted (char const*,int,char*,char const*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 scalar_t__ wait_ip_addr (char const*,int) ; 
 scalar_t__ wpa_command (char const*,char*) ; 
 int /*<<< orphan*/  wpa_ctrl_close (struct wpa_ctrl*) ; 
 int /*<<< orphan*/  wpa_ctrl_detach (struct wpa_ctrl*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  write_summary (struct hs20_osu_client*,char*) ; 

__attribute__((used)) static int osu_connect(struct hs20_osu_client *ctx, const char *bssid,
		       const char *ssid, const char *ssid2, const char *url,
		       unsigned int methods, int no_prod_assoc,
		       const char *osu_nai, const char *osu_nai2)
{
	int id;
	const char *ifname = ctx->ifname;
	char buf[200];
	struct wpa_ctrl *mon;
	int res;

	if (ssid2 && ssid2[0] == '\0')
		ssid2 = NULL;

	if (ctx->osu_ssid) {
		if (os_strcmp(ssid, ctx->osu_ssid) == 0) {
			wpa_printf(MSG_DEBUG,
				   "Enforced OSU SSID matches ANQP info");
			ssid2 = NULL;
		} else if (ssid2 && os_strcmp(ssid2, ctx->osu_ssid) == 0) {
			wpa_printf(MSG_DEBUG,
				   "Enforced OSU SSID matches RSN[OSEN] info");
			ssid = ssid2;
		} else {
			wpa_printf(MSG_INFO, "Enforced OSU SSID did not match");
			write_summary(ctx, "Enforced OSU SSID did not match");
			return -1;
		}
	}

	id = add_network(ifname);
	if (id < 0)
		return -1;
	if (set_network_quoted(ifname, id, "ssid", ssid) < 0)
		return -1;
	if (ssid2)
		osu_nai = osu_nai2;
	if (osu_nai && os_strlen(osu_nai) > 0) {
		char dir[255], fname[300];
		if (getcwd(dir, sizeof(dir)) == NULL)
			return -1;
		os_snprintf(fname, sizeof(fname), "%s/osu-ca.pem", dir);

		if (ssid2 && set_network_quoted(ifname, id, "ssid", ssid2) < 0)
			return -1;

		if (set_network(ifname, id, "proto", "OSEN") < 0 ||
		    set_network(ifname, id, "key_mgmt", "OSEN") < 0 ||
		    set_network(ifname, id, "pairwise", "CCMP") < 0 ||
		    set_network(ifname, id, "group", "GTK_NOT_USED CCMP") < 0 ||
		    set_network(ifname, id, "eap", "WFA-UNAUTH-TLS") < 0 ||
		    set_network(ifname, id, "ocsp", "2") < 0 ||
		    set_network_quoted(ifname, id, "identity", osu_nai) < 0 ||
		    set_network_quoted(ifname, id, "ca_cert", fname) < 0)
			return -1;
	} else if (ssid2) {
		wpa_printf(MSG_INFO, "No OSU_NAI set for RSN[OSEN]");
		write_summary(ctx, "No OSU_NAI set for RSN[OSEN]");
		return -1;
	} else {
		if (set_network(ifname, id, "key_mgmt", "NONE") < 0)
			return -1;
	}

	mon = open_wpa_mon(ifname);
	if (mon == NULL)
		return -1;

	wpa_printf(MSG_INFO, "Associate with OSU SSID");
	write_summary(ctx, "Associate with OSU SSID");
	snprintf(buf, sizeof(buf), "SELECT_NETWORK %d", id);
	if (wpa_command(ifname, buf) < 0)
		return -1;

	res = get_wpa_cli_event(mon, "CTRL-EVENT-CONNECTED",
				buf, sizeof(buf));

	wpa_ctrl_detach(mon);
	wpa_ctrl_close(mon);

	if (res < 0) {
		wpa_printf(MSG_INFO, "Could not connect");
		write_summary(ctx, "Could not connect to OSU network");
		wpa_printf(MSG_INFO, "Remove OSU network connection");
		snprintf(buf, sizeof(buf), "REMOVE_NETWORK %d", id);
		wpa_command(ifname, buf);
		return -1;
	}

	write_summary(ctx, "Waiting for IP address for subscription registration");
	if (wait_ip_addr(ifname, 15) < 0) {
		wpa_printf(MSG_INFO, "Could not get IP address for WLAN - try connection anyway");
	}

	if (no_prod_assoc) {
		if (res < 0)
			return -1;
		wpa_printf(MSG_INFO, "No production connection used for testing purposes");
		write_summary(ctx, "No production connection used for testing purposes");
		return 0;
	}

	ctx->no_reconnect = 1;
	if (methods & 0x02) {
		wpa_printf(MSG_DEBUG, "Calling cmd_prov from osu_connect");
		res = cmd_prov(ctx, url);
	} else if (methods & 0x01) {
		wpa_printf(MSG_DEBUG,
			   "Calling cmd_oma_dm_prov from osu_connect");
		res = cmd_oma_dm_prov(ctx, url);
	}

	wpa_printf(MSG_INFO, "Remove OSU network connection");
	write_summary(ctx, "Remove OSU network connection");
	snprintf(buf, sizeof(buf), "REMOVE_NETWORK %d", id);
	wpa_command(ifname, buf);

	if (res < 0)
		return -1;

	wpa_printf(MSG_INFO, "Requesting reconnection with updated configuration");
	write_summary(ctx, "Requesting reconnection with updated configuration");
	if (wpa_command(ctx->ifname, "INTERWORKING_SELECT auto") < 0) {
		wpa_printf(MSG_INFO, "Failed to request wpa_supplicant to reconnect");
		write_summary(ctx, "Failed to request wpa_supplicant to reconnect");
		return -1;
	}

	return 0;
}