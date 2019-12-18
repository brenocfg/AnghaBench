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
struct params {int dummy; } ;
struct ieee80211_frame {int* i_dur; int /*<<< orphan*/  i_addr1; int /*<<< orphan*/ * i_fc; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_FC0_SUBTYPE_CTS ; 
 int /*<<< orphan*/  IEEE80211_FC0_TYPE_CTL ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  send_frame (struct params*,struct ieee80211_frame*,int) ; 

void send_cts(struct params *p, char *mac)
{
	char buf[64];
	struct ieee80211_frame *wh;

	memset(buf, 0, sizeof(buf));
	wh = (struct ieee80211_frame*) buf;
	wh->i_fc[0] |= IEEE80211_FC0_TYPE_CTL;
	wh->i_fc[0] |= IEEE80211_FC0_SUBTYPE_CTS;
	wh->i_dur[0] = 0x69;
	wh->i_dur[1] = 0x00;
	memcpy(wh->i_addr1, mac, 6);

	send_frame(p, wh, 10);
}