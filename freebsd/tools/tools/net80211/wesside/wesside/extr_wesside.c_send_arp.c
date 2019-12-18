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
struct ieee80211_frame {int* i_fc; unsigned char* i_addr3; } ;
typedef  int /*<<< orphan*/  arp_pkt ;

/* Variables and functions */
 int /*<<< orphan*/  ETHERTYPE_ARP ; 
 int IEEE80211_FC0_TYPE_DATA ; 
 int IEEE80211_FC1_DIR_TODS ; 
 int IEEE80211_FC1_PROTECTED ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  do_arp (unsigned char*,unsigned short,unsigned char*,unsigned char*,unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  do_llc (unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_basic (struct ieee80211_frame*) ; 
 int /*<<< orphan*/  memset (unsigned char*,int,int) ; 
 int /*<<< orphan*/  send_frame (int,unsigned char*,int) ; 
 int /*<<< orphan*/  wepify (unsigned char*,int) ; 

void send_arp(int tx, unsigned short op, unsigned char* srcip, 
	      unsigned char* srcmac, unsigned char* dstip, 
	      unsigned char* dstmac) {
	
	static unsigned char arp_pkt[128];
	unsigned char* body;
	unsigned char* ptr;
	struct ieee80211_frame* wh;
	int arp_len;

	memset(arp_pkt, 0, sizeof(arp_pkt));

	// construct ARP
	wh = (struct ieee80211_frame*) arp_pkt;
	fill_basic(wh);

	wh->i_fc[0] |= IEEE80211_FC0_TYPE_DATA;
	wh->i_fc[1] |= IEEE80211_FC1_PROTECTED | IEEE80211_FC1_DIR_TODS;
	memset(wh->i_addr3, 0xff, 6);

	body = (unsigned char*) wh + sizeof(*wh);
	ptr = body;
	ptr += 4; // iv

	do_llc(ptr, ETHERTYPE_ARP);
	ptr += 8;
	do_arp(ptr, op, srcmac, srcip, dstmac, dstip);

	wepify(body, 8+8+20);
	arp_len = sizeof(*wh) + 4 + 8 + 8 + 20 + 4;
	assert(arp_len < sizeof(arp_pkt));

	send_frame(tx, arp_pkt, arp_len);
}