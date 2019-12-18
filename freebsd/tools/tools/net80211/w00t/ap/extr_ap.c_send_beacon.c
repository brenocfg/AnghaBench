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
struct params {int /*<<< orphan*/  blast; int /*<<< orphan*/  mac; } ;
struct ieee80211_frame {char* i_addr1; int /*<<< orphan*/ * i_fc; int /*<<< orphan*/  i_addr3; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_FC0_SUBTYPE_BEACON ; 
 int /*<<< orphan*/  IEEE80211_FC0_TYPE_MGT ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  fill_basic (struct ieee80211_frame*,struct params*) ; 
 int fill_beacon (struct params*,struct ieee80211_frame*) ; 
 int gettimeofday (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (char*,int,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  send_frame (struct params*,struct ieee80211_frame*,int) ; 

void send_beacon(struct params *p)
{
	char buf[4096];
	struct ieee80211_frame *wh;
	int len;
	char *ptr;

	wh = (struct ieee80211_frame*) buf;

	memset(buf, 0, sizeof(buf));
	fill_basic(wh, p);
	memset(wh->i_addr1, 0xff, 6);
	memcpy(wh->i_addr3, p->mac, 6);

	wh->i_fc[0] |= IEEE80211_FC0_TYPE_MGT;
	wh->i_fc[0] |= IEEE80211_FC0_SUBTYPE_BEACON;

	len = fill_beacon(p, wh);

	/* TIM */
	ptr = (char*)wh + len;
	*ptr++ = 5;
	*ptr++ = 4;
	len +=  2+4;
#if 0
	printf("sending beacon\n");
#endif	
	send_frame(p, wh, len);

	if (gettimeofday(&p->blast, NULL) == -1)
		err(1, "gettimeofday()");
}