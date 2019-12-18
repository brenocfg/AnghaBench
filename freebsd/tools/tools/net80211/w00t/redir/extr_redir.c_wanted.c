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
struct params {char* ap; char* mac; } ;
struct ieee80211_frame {int* i_fc; char* i_addr1; char* i_addr2; char* i_addr3; } ;

/* Variables and functions */
 int IEEE80211_FC1_DIR_TODS ; 
 int IEEE80211_FC1_PROTECTED ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

int wanted(struct params *p, struct ieee80211_frame *wh, int len)
{
	char *bssid, *sa;

	if (wh->i_fc[1] & IEEE80211_FC1_DIR_TODS) {
		bssid = wh->i_addr1;
		sa = wh->i_addr2;
	}	
	else {
		bssid = wh->i_addr2;
		sa = wh->i_addr3;
	}	

	if (memcmp(bssid, p->ap, 6) != 0)
		return 0;

	if (!(wh->i_fc[1] & IEEE80211_FC1_PROTECTED)) {
		printf("Got non WEP packet...\n");
		return 0;
	}

	/* my own shit */
	if (memcmp(p->mac, sa, 6) == 0)
		return 0;

	return 1;	
}