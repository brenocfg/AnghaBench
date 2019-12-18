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
struct params {int seq_rx; int /*<<< orphan*/  state; int /*<<< orphan*/  ap; int /*<<< orphan*/  mac; int /*<<< orphan*/  rx; } ;
struct ieee80211_frame {int* i_fc; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
#define  IEEE80211_FC0_SUBTYPE_ACK 129 
 int IEEE80211_FC0_SUBTYPE_DEAUTH ; 
 int IEEE80211_FC0_SUBTYPE_DISASSOC ; 
 int IEEE80211_FC0_SUBTYPE_MASK ; 
#define  IEEE80211_FC0_SUBTYPE_RTS 128 
 int IEEE80211_FC0_SUBTYPE_SHIFT ; 
 int IEEE80211_FC0_TYPE_CTL ; 
 int IEEE80211_FC0_TYPE_MASK ; 
 int IEEE80211_FC0_TYPE_MGT ; 
 int /*<<< orphan*/  S_ASSOCIATED ; 
 int /*<<< orphan*/  S_START ; 
 int /*<<< orphan*/  S_WAIT_ACK ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  for_me (struct ieee80211_frame*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  from_ap (struct ieee80211_frame*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_process (struct ieee80211_frame*,struct params*,int) ; 
 struct ieee80211_frame* get_wifi (char*,int*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int sniff (int /*<<< orphan*/ ,char*,int) ; 

void read_wifi(struct params *p)
{
	char buf[4096];
	int rc;
	struct ieee80211_frame *wh;
	int type, stype;

	rc = sniff(p->rx, buf, sizeof(buf));
	if (rc == -1)
		err(1, "sniff()");

	wh = get_wifi(buf, &rc);
	if (!wh)
		return;

	generic_process(wh, p, rc);

	if (!for_me(wh, p->mac))
		return;

	type = wh->i_fc[0] & IEEE80211_FC0_TYPE_MASK;
	stype = wh->i_fc[0] & IEEE80211_FC0_SUBTYPE_MASK;

	/* control frames */
	if (type == IEEE80211_FC0_TYPE_CTL) {
		switch (stype) {
		case IEEE80211_FC0_SUBTYPE_ACK:
			if (p->state == S_WAIT_ACK)
				p->state = S_ASSOCIATED;
			break;
		
		case IEEE80211_FC0_SUBTYPE_RTS:
#if 0		
			printf("Got RTS\n");
#endif			
			break;
	
		default:
			printf("Unknown CTL frame %d\n",
			       stype >> IEEE80211_FC0_SUBTYPE_SHIFT);
			abort();
			break;
		}
		return;
	}

	if (!from_ap(wh, p->ap))
		return;

	if (type != IEEE80211_FC0_TYPE_MGT)
		return;

	if (stype == IEEE80211_FC0_SUBTYPE_DEAUTH ||
	    stype == IEEE80211_FC0_SUBTYPE_DISASSOC) {
		printf("Got management! %d\n",
		       stype >> IEEE80211_FC0_SUBTYPE_SHIFT);
		p->seq_rx = -1;
		p->state = S_START;
	}

	return;
}