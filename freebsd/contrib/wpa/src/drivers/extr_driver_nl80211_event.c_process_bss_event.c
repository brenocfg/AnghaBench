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
struct nlattr {int dummy; } ;
struct nl_msg {int dummy; } ;
struct i802_bss {int /*<<< orphan*/  drv; int /*<<< orphan*/  ifname; } ;
struct genlmsghdr {int cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 size_t NL80211_ATTR_ACK ; 
 size_t NL80211_ATTR_COOKIE ; 
 size_t NL80211_ATTR_FRAME ; 
 size_t NL80211_ATTR_MAC ; 
 int /*<<< orphan*/  NL80211_ATTR_MAX ; 
 size_t NL80211_ATTR_RX_SIGNAL_DBM ; 
 size_t NL80211_ATTR_STA_WME ; 
 size_t NL80211_ATTR_TIMED_OUT ; 
 size_t NL80211_ATTR_WIPHY_FREQ ; 
#define  NL80211_CMD_EXTERNAL_AUTH 132 
#define  NL80211_CMD_FRAME 131 
#define  NL80211_CMD_FRAME_TX_STATUS 130 
#define  NL80211_CMD_UNEXPECTED_4ADDR_FRAME 129 
#define  NL80211_CMD_UNEXPECTED_FRAME 128 
 int NL_SKIP ; 
 int /*<<< orphan*/  genlmsg_attrdata (struct genlmsghdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genlmsg_attrlen (struct genlmsghdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlme_event (struct i802_bss*,int,struct nlattr*,struct nlattr*,struct nlattr*,struct nlattr*,struct nlattr*,struct nlattr*,struct nlattr*,struct nlattr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nl80211_command_to_string (int) ; 
 int /*<<< orphan*/  nl80211_external_auth (int /*<<< orphan*/ ,struct nlattr**) ; 
 int /*<<< orphan*/  nl80211_spurious_frame (struct i802_bss*,struct nlattr**,int) ; 
 int /*<<< orphan*/  nla_parse (struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct genlmsghdr* nlmsg_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_hdr (struct nl_msg*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int,...) ; 

int process_bss_event(struct nl_msg *msg, void *arg)
{
	struct i802_bss *bss = arg;
	struct genlmsghdr *gnlh = nlmsg_data(nlmsg_hdr(msg));
	struct nlattr *tb[NL80211_ATTR_MAX + 1];

	nla_parse(tb, NL80211_ATTR_MAX, genlmsg_attrdata(gnlh, 0),
		  genlmsg_attrlen(gnlh, 0), NULL);

	wpa_printf(MSG_DEBUG, "nl80211: BSS Event %d (%s) received for %s",
		   gnlh->cmd, nl80211_command_to_string(gnlh->cmd),
		   bss->ifname);

	switch (gnlh->cmd) {
	case NL80211_CMD_FRAME:
	case NL80211_CMD_FRAME_TX_STATUS:
		mlme_event(bss, gnlh->cmd, tb[NL80211_ATTR_FRAME],
			   tb[NL80211_ATTR_MAC], tb[NL80211_ATTR_TIMED_OUT],
			   tb[NL80211_ATTR_WIPHY_FREQ], tb[NL80211_ATTR_ACK],
			   tb[NL80211_ATTR_COOKIE],
			   tb[NL80211_ATTR_RX_SIGNAL_DBM],
			   tb[NL80211_ATTR_STA_WME], NULL);
		break;
	case NL80211_CMD_UNEXPECTED_FRAME:
		nl80211_spurious_frame(bss, tb, 0);
		break;
	case NL80211_CMD_UNEXPECTED_4ADDR_FRAME:
		nl80211_spurious_frame(bss, tb, 1);
		break;
	case NL80211_CMD_EXTERNAL_AUTH:
		nl80211_external_auth(bss->drv, tb);
		break;
	default:
		wpa_printf(MSG_DEBUG, "nl80211: Ignored unknown event "
			   "(cmd=%d)", gnlh->cmd);
		break;
	}

	return NL_SKIP;
}