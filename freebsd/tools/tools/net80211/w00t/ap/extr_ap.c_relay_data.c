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
struct params {char* mac; int /*<<< orphan*/  seq; } ;
struct ieee80211_frame {char* i_fc; char* i_seq; char* i_addr1; char* i_addr3; char* i_addr2; } ;
typedef  int /*<<< orphan*/  seq ;
typedef  int /*<<< orphan*/  fc ;

/* Variables and functions */
 int IEEE80211_FC1_DIR_FROMDS ; 
 int IEEE80211_FC1_DIR_TODS ; 
 int IEEE80211_FC1_RETRY ; 
 int /*<<< orphan*/  enque (struct params*,struct ieee80211_frame*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  send_frame (struct params*,struct ieee80211_frame*,int) ; 
 unsigned short seqfn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void relay_data(struct params *p, struct ieee80211_frame *wh, int len)
{
	char seq[2];
	char fc[2];
	unsigned short *ps;

	/* copy crap */
	memcpy(fc, wh->i_fc, 2);
	memcpy(seq, wh->i_seq, 2);

	/* relay frame */
	wh->i_fc[1] &= ~(IEEE80211_FC1_DIR_TODS | IEEE80211_FC1_RETRY);
	wh->i_fc[1] |= IEEE80211_FC1_DIR_FROMDS;
	memcpy(wh->i_addr1, wh->i_addr3, sizeof(wh->i_addr1));
	memcpy(wh->i_addr3, wh->i_addr2, sizeof(wh->i_addr3));
	memcpy(wh->i_addr2, p->mac, sizeof(wh->i_addr2));
        ps = (unsigned short*)wh->i_seq;
        *ps = seqfn(p->seq, 0);
	
	send_frame(p, wh, len);
	enque(p, wh, len);

	/* restore */
	memcpy(wh->i_fc, fc, sizeof(fc));
	memcpy(wh->i_addr2, wh->i_addr3, sizeof(wh->i_addr2));
	memcpy(wh->i_addr3, wh->i_addr1, sizeof(wh->i_addr2));
	memcpy(wh->i_addr1, p->mac, sizeof(wh->i_addr1));
	memcpy(wh->i_seq, seq, sizeof(seq));
}