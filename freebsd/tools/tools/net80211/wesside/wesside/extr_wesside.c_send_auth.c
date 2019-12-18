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
struct ieee80211_frame {int* i_fc; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int IEEE80211_FC0_SUBTYPE_AUTH ; 
 int IEEE80211_FC0_TYPE_MGT ; 
 int /*<<< orphan*/  fill_basic (struct ieee80211_frame*) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  send_frame (int,unsigned char*,int) ; 

void send_auth(int tx) {
	unsigned char buf[128];
	struct ieee80211_frame* wh = (struct ieee80211_frame*) buf;
	unsigned short* n;

	memset(buf, 0, sizeof(buf));
	fill_basic(wh);
	wh->i_fc[0] |= IEEE80211_FC0_TYPE_MGT | IEEE80211_FC0_SUBTYPE_AUTH;

	n = (unsigned short*) ((unsigned char*) wh + sizeof(*wh));
	n++;
	*n = 1;

	send_frame(tx, buf, sizeof(*wh) + 2 + 2 + 2);
}