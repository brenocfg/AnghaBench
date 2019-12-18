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
struct params {int /*<<< orphan*/  mac; int /*<<< orphan*/  rx; } ;
struct ieee80211_frame {int* i_fc; int /*<<< orphan*/  i_addr2; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
#define  IEEE80211_FC0_TYPE_CTL 130 
#define  IEEE80211_FC0_TYPE_DATA 129 
 int IEEE80211_FC0_TYPE_MASK ; 
#define  IEEE80211_FC0_TYPE_MGT 128 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  ack (struct params*,struct ieee80211_frame*) ; 
 scalar_t__ duplicate (struct params*,struct ieee80211_frame*,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 struct ieee80211_frame* get_wifi (char*,int*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  read_ctl (struct params*,struct ieee80211_frame*,int) ; 
 int /*<<< orphan*/  read_data (struct params*,struct ieee80211_frame*,int) ; 
 int /*<<< orphan*/  read_mgt (struct params*,struct ieee80211_frame*,int) ; 
 int sniff (int /*<<< orphan*/ ,char*,int) ; 

void read_wifi(struct params *p)
{
	char buf[4096];
	int rc;
	struct ieee80211_frame *wh;

	rc = sniff(p->rx, buf, sizeof(buf));
	if (rc == -1)
		err(1, "sniff()");
        
	wh = get_wifi(buf, &rc);
	if (!wh)
		return;

	/* filter my own shit */
	if (memcmp(wh->i_addr2, p->mac, 6) == 0) {
		/* XXX CTL frames */
		if ((wh->i_fc[0] & IEEE80211_FC0_TYPE_MASK) !=
		    IEEE80211_FC0_TYPE_CTL)
			return;
	}

#if 1
	ack(p, wh);
#endif

	if (duplicate(p, wh, rc)) {
#if 0
		printf("Dup\n");
#endif		
		return;
	}

	switch (wh->i_fc[0] & IEEE80211_FC0_TYPE_MASK) {
	case IEEE80211_FC0_TYPE_MGT:
		read_mgt(p, wh, rc);
		break;
		
	case IEEE80211_FC0_TYPE_CTL:
		read_ctl(p, wh, rc);
		break;
	
	case IEEE80211_FC0_TYPE_DATA:
		read_data(p, wh, rc);
		break;
	
	default:
		printf("wtf\n");
		abort();
		break;
	}
}