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
struct params {scalar_t__ state; int /*<<< orphan*/  mac; int /*<<< orphan*/  rx; } ;
struct ieee80211_frame {int /*<<< orphan*/  i_addr1; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_FC0_SUBTYPE_ACK ; 
 int /*<<< orphan*/  IEEE80211_FC0_SUBTYPE_DATA ; 
 int /*<<< orphan*/  IEEE80211_FC0_TYPE_CTL ; 
 int /*<<< orphan*/  IEEE80211_FC0_TYPE_DATA ; 
 scalar_t__ S_START ; 
 int /*<<< orphan*/  enque (struct params*,char**,struct ieee80211_frame*,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ frame_type (struct ieee80211_frame*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ieee80211_frame* get_wifi (char*,int*) ; 
 int /*<<< orphan*/  got_ack (struct params*) ; 
 scalar_t__ malloc (int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  send_queue (struct params*) ; 
 int sniff (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wanted (struct params*,struct ieee80211_frame*,int) ; 

void read_wifi(struct params *p)
{
	static char *buf = 0;
	static int buflen = 4096;
	struct ieee80211_frame *wh;
	int rc;

	if (!buf) {
		buf = (char*) malloc(buflen);
		if (!buf)
			err(1, "malloc()");
	}
	
	rc = sniff(p->rx, buf, buflen);
	if (rc == -1)
		err(1, "sniff()");

	wh = get_wifi(buf, &rc);
	if (!wh)
		return;

	/* acks */
	if (frame_type(wh, IEEE80211_FC0_TYPE_CTL, IEEE80211_FC0_SUBTYPE_ACK) &&
	    (memcmp(p->mac, wh->i_addr1, 6) == 0)) {
		got_ack(p);
		return;
	}

	/* data */
	if (frame_type(wh, IEEE80211_FC0_TYPE_DATA,
		       IEEE80211_FC0_SUBTYPE_DATA)) {
		if (!wanted(p, wh, rc))
			return;
		
		enque(p, &buf, wh, rc);
		if (p->state == S_START)
			send_queue(p);
		return;
	}
}