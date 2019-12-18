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
struct params {int /*<<< orphan*/  bssid; int /*<<< orphan*/  ap; int /*<<< orphan*/  ssid; int /*<<< orphan*/  mac; int /*<<< orphan*/  rx; } ;
struct ieee80211_frame {int /*<<< orphan*/  i_addr3; int /*<<< orphan*/  i_addr2; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 char IEEE80211_CAPINFO_PRIVACY ; 
 int /*<<< orphan*/  IEEE80211_FC0_SUBTYPE_PROBE_RESP ; 
 int /*<<< orphan*/  IEEE80211_FC0_TYPE_MGT ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  for_me (struct ieee80211_frame*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frame_type (struct ieee80211_frame*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_process (struct ieee80211_frame*,struct params*,int) ; 
 struct ieee80211_frame* get_wifi (char*,int*) ; 
 int /*<<< orphan*/  mac2str (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int sniff (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

int get_probe_response(struct params *p)
{
	char buf[4096];
	int rc;
	struct ieee80211_frame *wh;
	char *data;
	int ess;
	int wep;
	char *ssid;
	char from[18];
	char bssid[18];

	rc = sniff(p->rx, buf, sizeof(buf));
	if (rc == -1)
		err(1, "sniff()");

	wh = get_wifi(buf, &rc);
	if (!wh)
		return 0;

	generic_process(wh, p, rc);

	if (!for_me(wh, p->mac))
		return 0;

	if (!frame_type(wh, IEEE80211_FC0_TYPE_MGT,
			IEEE80211_FC0_SUBTYPE_PROBE_RESP))
		return 0;

	data = (char*) (wh+1);
	data += 8; /* Timestamp */
	data += 2; /* Beacon Interval */
	ess = *data & 1;
	wep = (*data & IEEE80211_CAPINFO_PRIVACY) ? 1 : 0;
	data += 2; /* capability */

	/* ssid */
	if (*data != 0) {
		printf("Warning, expecting SSID got %x\n", *data);
		return 0;
	}
	data++;
	ssid = data+1;
	data += 1 + *data;
	if (*data != 1) {
		printf("Warning, expected rates got %x\n", *data);
		return 0;
	}
	*data = 0;

	/* rates */
	data++;

	mac2str(from, wh->i_addr2);
	mac2str(bssid, wh->i_addr3);
	printf("Got response from %s [%s] [%s] ESS=%d WEP=%d\n",
	       from, bssid, ssid, ess, wep);

	if (strcmp(ssid, p->ssid) != 0)
		return 0;

	memcpy(p->ap, wh->i_addr2, 6);
	memcpy(p->bssid, wh->i_addr3, 6);
	return 1;
}