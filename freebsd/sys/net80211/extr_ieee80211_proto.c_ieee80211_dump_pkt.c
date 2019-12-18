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
typedef  int uint8_t ;
struct ieee80211com {int dummy; } ;
struct ieee80211_qosframe {int* i_qos; } ;
struct ieee80211_frame {int* i_fc; int const* i_addr2; int const* i_addr1; int const* i_addr3; } ;

/* Variables and functions */
#define  IEEE80211_FC0_TYPE_DATA 133 
 int IEEE80211_FC0_TYPE_MASK ; 
#define  IEEE80211_FC0_TYPE_MGT 132 
#define  IEEE80211_FC1_DIR_DSTODS 131 
#define  IEEE80211_FC1_DIR_FROMDS 130 
 int IEEE80211_FC1_DIR_MASK ; 
#define  IEEE80211_FC1_DIR_NODS 129 
#define  IEEE80211_FC1_DIR_TODS 128 
 int IEEE80211_FC1_PROTECTED ; 
 int IEEE80211_QOS_ACKPOLICY ; 
 scalar_t__ IEEE80211_QOS_HAS_SEQ (struct ieee80211_frame const*) ; 
 int IEEE80211_QOS_TID ; 
 int const IEEE80211_WEP_EXTIV ; 
 int IEEE80211_WEP_IVLEN ; 
 char* ether_sprintf (int const*) ; 
 int ieee80211_anyhdrspace (struct ieee80211com*,struct ieee80211_frame const*) ; 
 char* ieee80211_mgt_subtype_name (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void
ieee80211_dump_pkt(struct ieee80211com *ic,
	const uint8_t *buf, int len, int rate, int rssi)
{
	const struct ieee80211_frame *wh;
	int i;

	wh = (const struct ieee80211_frame *)buf;
	switch (wh->i_fc[1] & IEEE80211_FC1_DIR_MASK) {
	case IEEE80211_FC1_DIR_NODS:
		printf("NODS %s", ether_sprintf(wh->i_addr2));
		printf("->%s", ether_sprintf(wh->i_addr1));
		printf("(%s)", ether_sprintf(wh->i_addr3));
		break;
	case IEEE80211_FC1_DIR_TODS:
		printf("TODS %s", ether_sprintf(wh->i_addr2));
		printf("->%s", ether_sprintf(wh->i_addr3));
		printf("(%s)", ether_sprintf(wh->i_addr1));
		break;
	case IEEE80211_FC1_DIR_FROMDS:
		printf("FRDS %s", ether_sprintf(wh->i_addr3));
		printf("->%s", ether_sprintf(wh->i_addr1));
		printf("(%s)", ether_sprintf(wh->i_addr2));
		break;
	case IEEE80211_FC1_DIR_DSTODS:
		printf("DSDS %s", ether_sprintf((const uint8_t *)&wh[1]));
		printf("->%s", ether_sprintf(wh->i_addr3));
		printf("(%s", ether_sprintf(wh->i_addr2));
		printf("->%s)", ether_sprintf(wh->i_addr1));
		break;
	}
	switch (wh->i_fc[0] & IEEE80211_FC0_TYPE_MASK) {
	case IEEE80211_FC0_TYPE_DATA:
		printf(" data");
		break;
	case IEEE80211_FC0_TYPE_MGT:
		printf(" %s", ieee80211_mgt_subtype_name(wh->i_fc[0]));
		break;
	default:
		printf(" type#%d", wh->i_fc[0] & IEEE80211_FC0_TYPE_MASK);
		break;
	}
	if (IEEE80211_QOS_HAS_SEQ(wh)) {
		const struct ieee80211_qosframe *qwh = 
			(const struct ieee80211_qosframe *)buf;
		printf(" QoS [TID %u%s]", qwh->i_qos[0] & IEEE80211_QOS_TID,
			qwh->i_qos[0] & IEEE80211_QOS_ACKPOLICY ? " ACM" : "");
	}
	if (wh->i_fc[1] & IEEE80211_FC1_PROTECTED) {
		int off;

		off = ieee80211_anyhdrspace(ic, wh);
		printf(" WEP [IV %.02x %.02x %.02x",
			buf[off+0], buf[off+1], buf[off+2]);
		if (buf[off+IEEE80211_WEP_IVLEN] & IEEE80211_WEP_EXTIV)
			printf(" %.02x %.02x %.02x",
				buf[off+4], buf[off+5], buf[off+6]);
		printf(" KID %u]", buf[off+IEEE80211_WEP_IVLEN] >> 6);
	}
	if (rate >= 0)
		printf(" %dM", rate / 2);
	if (rssi >= 0)
		printf(" +%d", rssi);
	printf("\n");
	if (len > 0) {
		for (i = 0; i < len; i++) {
			if ((i & 1) == 0)
				printf(" ");
			printf("%02x", buf[i]);
		}
		printf("\n");
	}
}