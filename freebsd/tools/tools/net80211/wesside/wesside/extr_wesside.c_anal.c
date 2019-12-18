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
struct ieee80211_frame {int* i_fc; int /*<<< orphan*/  i_addr2; int /*<<< orphan*/  i_addr1; scalar_t__ i_seq; } ;
struct TYPE_2__ {int /*<<< orphan*/  bss; } ;

/* Variables and functions */
 scalar_t__ FIND_VICTIM ; 
 scalar_t__ FOUND_VICTIM ; 
 int IEEE80211_FC0_SUBTYPE_BEACON ; 
 int IEEE80211_FC0_SUBTYPE_MASK ; 
 int IEEE80211_FC0_SUBTYPE_PROBE_RESP ; 
 int IEEE80211_FC0_TYPE_CTL ; 
 int IEEE80211_FC0_TYPE_MASK ; 
 int IEEE80211_FC0_TYPE_MGT ; 
 int IEEE80211_FC1_DIR_FROMDS ; 
 int IEEE80211_FC1_DIR_TODS ; 
 int IEEE80211_FC1_RETRY ; 
 unsigned short IEEE80211_SEQ_SEQ_MASK ; 
 unsigned short IEEE80211_SEQ_SEQ_SHIFT ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ get_victim_ssid (struct ieee80211_frame*,int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mymac ; 
 int /*<<< orphan*/  send_ack (int) ; 
 scalar_t__ state ; 
 int /*<<< orphan*/  stuff_for_net (struct ieee80211_frame*,int) ; 
 int /*<<< orphan*/  stuff_for_us (struct ieee80211_frame*,int) ; 
 int /*<<< orphan*/  time_print (char*,int) ; 
 TYPE_1__ victim ; 

void anal(unsigned char* buf, int rd, int tx) { // yze
	struct ieee80211_frame* wh = (struct ieee80211_frame *) buf;
	int type,stype;
	static int lastseq = -1;
	int seq;
	unsigned short *seqptr;
	int for_us = 0;

	if (rd < 1) {
		time_print("rd=%d\n", rd);
		exit(1);
	}

	type = wh->i_fc[0] & IEEE80211_FC0_TYPE_MASK;
	stype = wh->i_fc[0] & IEEE80211_FC0_SUBTYPE_MASK;

	// sort out acks
	if (state >= FOUND_VICTIM) {
		// stuff for us
		if (memcmp(wh->i_addr1, mymac, 6) == 0) {
			for_us = 1;
			if (type != IEEE80211_FC0_TYPE_CTL)
				send_ack(tx);
		}
	}	
	
	// XXX i know it aint great...
	seqptr = (unsigned short*)  wh->i_seq;
	seq = (*seqptr & IEEE80211_SEQ_SEQ_MASK) >> IEEE80211_SEQ_SEQ_SHIFT;
	if (seq == lastseq && (wh->i_fc[1] & IEEE80211_FC1_RETRY) &&
	    type != IEEE80211_FC0_TYPE_CTL) {
//		printf("Ignoring dup packet... seq=%d\n", seq);
		return;
	}
	lastseq = seq;

	// management frame
	if (type == IEEE80211_FC0_TYPE_MGT) {
		if(state == FIND_VICTIM) {
			if (stype == IEEE80211_FC0_SUBTYPE_BEACON ||
			    stype == IEEE80211_FC0_SUBTYPE_PROBE_RESP) {

			    	if (get_victim_ssid(wh, rd)) {
			    		return;
				}
			}
			    
		}
	}

	if (state >= FOUND_VICTIM) {
		// stuff for us
		if (for_us) {
			stuff_for_us(wh, rd);
		}

		// stuff in network [even for us]
		if ( ((wh->i_fc[1] & IEEE80211_FC1_DIR_TODS) &&
			  (memcmp(victim.bss, wh->i_addr1, 6) == 0)) || 
			  
			  ((wh->i_fc[1] & IEEE80211_FC1_DIR_FROMDS) &&
			  (memcmp(victim.bss, wh->i_addr2, 6) == 0))
			   ) {
			stuff_for_net(wh, rd);
		}
	}
}