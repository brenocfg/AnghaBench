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
struct ieee80211_frame {int* i_fc; unsigned char* i_addr3; unsigned char* i_addr1; } ;

/* Variables and functions */
 scalar_t__ FOUND_VICTIM ; 
 int IEEE80211_FC0_SUBTYPE_DATA ; 
 int IEEE80211_FC0_SUBTYPE_MASK ; 
 int IEEE80211_FC0_TYPE_DATA ; 
 int IEEE80211_FC0_TYPE_MASK ; 
 int IEEE80211_FC1_DIR_FROMDS ; 
 int IEEE80211_FC1_DIR_TODS ; 
 int IEEE80211_FC1_PROTECTED ; 
 scalar_t__ SPOOF_MAC ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  got_wep (struct ieee80211_frame*,int) ; 
 int /*<<< orphan*/  mac2str (unsigned char*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 unsigned char* mymac ; 
 scalar_t__ state ; 
 int /*<<< orphan*/  time_print (char*,int /*<<< orphan*/ ) ; 

void stuff_for_net(struct ieee80211_frame* wh, int rd) {
	int type,stype;
	
	type = wh->i_fc[0] & IEEE80211_FC0_TYPE_MASK;
	stype = wh->i_fc[0] & IEEE80211_FC0_SUBTYPE_MASK;

	if (type == IEEE80211_FC0_TYPE_DATA && 
	    stype == IEEE80211_FC0_SUBTYPE_DATA) {
		int dlen = rd - sizeof(struct ieee80211_frame);

		if (state == SPOOF_MAC) {
			unsigned char mac[6];
			if (wh->i_fc[1] & IEEE80211_FC1_DIR_TODS) {
				memcpy(mac, wh->i_addr3, 6);
			} else if (wh->i_fc[1] & IEEE80211_FC1_DIR_FROMDS) {
				memcpy(mac, wh->i_addr1, 6);
			} else assert(0);

			if (mac[0] == 0xff || mac[0] == 0x1)
				return;

			memcpy(mymac, mac, 6);	
			time_print("Trying to use MAC=(%s)\n", mac2str(mymac));
			state = FOUND_VICTIM;
			return;
		}

		// wep data!
		if ( (wh->i_fc[1] & IEEE80211_FC1_PROTECTED) &&
		    dlen > (4+8+4)) {
			got_wep(wh, rd);
		}
	}
}