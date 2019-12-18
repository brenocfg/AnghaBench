#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct node_info {int wep; int ap; int /*<<< orphan*/  mac; scalar_t__* ssid; int /*<<< orphan*/  chan; } ;
struct ieee80211_frame {int* i_fc; scalar_t__* i_addr2; } ;
struct TYPE_2__ {int /*<<< orphan*/  chan; } ;

/* Variables and functions */
 int CRYPT_WEP ; 
 int CRYPT_WPA ; 
 int IEEE80211_FC0_SUBTYPE_BEACON ; 
 int IEEE80211_FC0_SUBTYPE_DATA ; 
 int IEEE80211_FC0_SUBTYPE_MASK ; 
 int IEEE80211_FC0_TYPE_CTL ; 
 int IEEE80211_FC0_TYPE_DATA ; 
 int IEEE80211_FC0_TYPE_MASK ; 
 int IEEE80211_FC0_TYPE_MGT ; 
 int IEEE80211_FC1_DIR_FROMDS ; 
 int IEEE80211_FC1_PROTECTED ; 
 TYPE_1__ chaninfo ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  get_beacon_info (unsigned char*,int,struct node_info*) ; 
 int /*<<< orphan*/  mac2str (scalar_t__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  mvprintw (int,int,char*,...) ; 

int get_packet_info(struct ieee80211_frame* wh, 
		     unsigned char* body, int bodylen,
		     struct node_info* node) {
	
	int type, stype;

	node->chan = chaninfo.chan;
	node->wep = -1;
	node->ssid[0] = 0;
	node->ap = -1;
	
	type = wh->i_fc[0] & IEEE80211_FC0_TYPE_MASK;
	
	if (type == IEEE80211_FC0_TYPE_CTL)
		return 0;
#if 0
	if (wh->i_addr2[0] != 0) {
		mvprintw(30,30,"%s %x",mac2str(wh->i_addr2), wh->i_fc[0]);
	}	
#endif

	stype = wh->i_fc[0] & IEEE80211_FC0_SUBTYPE_MASK;
	
	if (type == IEEE80211_FC0_TYPE_MGT &&
	    stype == IEEE80211_FC0_SUBTYPE_BEACON) {
		get_beacon_info(body, bodylen, node);
		node->ap = 1;
	}	

	else if (type == IEEE80211_FC0_TYPE_DATA &&
	    stype == IEEE80211_FC0_SUBTYPE_DATA) {
	
		if (wh->i_fc[1] & IEEE80211_FC1_PROTECTED) {
			unsigned char* iv;
			
			node->wep = CRYPT_WEP;

			iv = body;
			iv += 3;

			// extended IV?
			if (*iv & (1 << 1)) {
#if 0				
				node->wep = CRYPT_WPA;
				mvprintw(20,20, "shei");
				exit(1);
#endif				
			}
		}	
	
		if (wh->i_fc[1] & IEEE80211_FC1_DIR_FROMDS)
			node->ap = 1;
		else
			node->ap = 0;
	}    
	
	memcpy(node->mac, wh->i_addr2, 6);
	return 1;	
}