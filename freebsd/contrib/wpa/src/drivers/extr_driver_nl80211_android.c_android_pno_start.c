#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wpa_driver_scan_params {size_t num_ssids; TYPE_1__* ssids; } ;
struct wpa_driver_nl80211_data {TYPE_2__* global; } ;
struct ifreq {char* buf; int used_len; int total_len; struct ifreq* ifr_data; int /*<<< orphan*/  ifr_name; } ;
struct i802_bss {int /*<<< orphan*/  ifname; struct wpa_driver_nl80211_data* drv; } ;
typedef  int /*<<< orphan*/  priv_cmd ;
typedef  int /*<<< orphan*/  ifr ;
typedef  int /*<<< orphan*/  buf ;
typedef  struct ifreq android_wifi_priv_cmd ;
struct TYPE_4__ {int /*<<< orphan*/  ioctl_sock; } ;
struct TYPE_3__ {char ssid_len; int /*<<< orphan*/  ssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFNAMSIZ ; 
 int MAX_SSID_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 scalar_t__ SIOCDEVPRIVATE ; 
 int /*<<< orphan*/  WEXT_PNOSETUP_HEADER ; 
 int WEXT_PNOSETUP_HEADER_SIZE ; 
 int WEXT_PNO_AMOUNT ; 
 int WEXT_PNO_MAX_COMMAND_SIZE ; 
 int /*<<< orphan*/  WEXT_PNO_MAX_REPEAT ; 
 scalar_t__ WEXT_PNO_MAX_REPEAT_LENGTH ; 
 char WEXT_PNO_MAX_REPEAT_SECTION ; 
 int WEXT_PNO_NONSSID_SECTIONS_SIZE ; 
 int /*<<< orphan*/  WEXT_PNO_REPEAT ; 
 scalar_t__ WEXT_PNO_REPEAT_LENGTH ; 
 char WEXT_PNO_REPEAT_SECTION ; 
 int /*<<< orphan*/  WEXT_PNO_SCAN_INTERVAL ; 
 scalar_t__ WEXT_PNO_SCAN_INTERVAL_LENGTH ; 
 char WEXT_PNO_SCAN_INTERVAL_SECTION ; 
 int WEXT_PNO_SSID_HEADER_SIZE ; 
 char WEXT_PNO_SSID_SECTION ; 
 char WEXT_PNO_TLV_PREFIX ; 
 char WEXT_PNO_TLV_RESERVED ; 
 char WEXT_PNO_TLV_SUBVERSION ; 
 char WEXT_PNO_TLV_VERSION ; 
 int android_priv_cmd (struct i802_bss*,char*) ; 
 scalar_t__ drv_errors ; 
 int ioctl (int /*<<< orphan*/ ,scalar_t__,struct ifreq*) ; 
 int /*<<< orphan*/  memset (struct ifreq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  os_memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  os_snprintf (char*,scalar_t__,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_driver_send_hang_msg (struct wpa_driver_nl80211_data*) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int) ; 

int android_pno_start(struct i802_bss *bss,
		      struct wpa_driver_scan_params *params)
{
	struct wpa_driver_nl80211_data *drv = bss->drv;
	struct ifreq ifr;
	android_wifi_priv_cmd priv_cmd;
	int ret = 0, i = 0, bp;
	char buf[WEXT_PNO_MAX_COMMAND_SIZE];

	bp = WEXT_PNOSETUP_HEADER_SIZE;
	os_memcpy(buf, WEXT_PNOSETUP_HEADER, bp);
	buf[bp++] = WEXT_PNO_TLV_PREFIX;
	buf[bp++] = WEXT_PNO_TLV_VERSION;
	buf[bp++] = WEXT_PNO_TLV_SUBVERSION;
	buf[bp++] = WEXT_PNO_TLV_RESERVED;

	while (i < WEXT_PNO_AMOUNT && (size_t) i < params->num_ssids) {
		/* Check that there is enough space needed for 1 more SSID, the
		 * other sections and null termination */
		if ((bp + WEXT_PNO_SSID_HEADER_SIZE + MAX_SSID_LEN +
		     WEXT_PNO_NONSSID_SECTIONS_SIZE + 1) >= (int) sizeof(buf))
			break;
		wpa_hexdump_ascii(MSG_DEBUG, "For PNO Scan",
				  params->ssids[i].ssid,
				  params->ssids[i].ssid_len);
		buf[bp++] = WEXT_PNO_SSID_SECTION;
		buf[bp++] = params->ssids[i].ssid_len;
		os_memcpy(&buf[bp], params->ssids[i].ssid,
			  params->ssids[i].ssid_len);
		bp += params->ssids[i].ssid_len;
		i++;
	}

	buf[bp++] = WEXT_PNO_SCAN_INTERVAL_SECTION;
	os_snprintf(&buf[bp], WEXT_PNO_SCAN_INTERVAL_LENGTH + 1, "%x",
		    WEXT_PNO_SCAN_INTERVAL);
	bp += WEXT_PNO_SCAN_INTERVAL_LENGTH;

	buf[bp++] = WEXT_PNO_REPEAT_SECTION;
	os_snprintf(&buf[bp], WEXT_PNO_REPEAT_LENGTH + 1, "%x",
		    WEXT_PNO_REPEAT);
	bp += WEXT_PNO_REPEAT_LENGTH;

	buf[bp++] = WEXT_PNO_MAX_REPEAT_SECTION;
	os_snprintf(&buf[bp], WEXT_PNO_MAX_REPEAT_LENGTH + 1, "%x",
		    WEXT_PNO_MAX_REPEAT);
	bp += WEXT_PNO_MAX_REPEAT_LENGTH + 1;

	memset(&ifr, 0, sizeof(ifr));
	memset(&priv_cmd, 0, sizeof(priv_cmd));
	os_strlcpy(ifr.ifr_name, bss->ifname, IFNAMSIZ);

	priv_cmd.buf = buf;
	priv_cmd.used_len = bp;
	priv_cmd.total_len = bp;
	ifr.ifr_data = &priv_cmd;

	ret = ioctl(drv->global->ioctl_sock, SIOCDEVPRIVATE + 1, &ifr);

	if (ret < 0) {
		wpa_printf(MSG_ERROR, "ioctl[SIOCSIWPRIV] (pnosetup): %d",
			   ret);
		wpa_driver_send_hang_msg(drv);
		return ret;
	}

	drv_errors = 0;

	return android_priv_cmd(bss, "PNOFORCE 1");
}