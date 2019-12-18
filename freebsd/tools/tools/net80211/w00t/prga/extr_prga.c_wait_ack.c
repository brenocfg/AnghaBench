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
struct timeval {int tv_sec; int tv_usec; } ;
struct params {int data_try; scalar_t__ frag; int /*<<< orphan*/  state; struct timeval last; int /*<<< orphan*/  mac; scalar_t__ rx; } ;
struct ieee80211_frame {int /*<<< orphan*/  i_addr1; } ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  FD_ISSET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IEEE80211_FC0_SUBTYPE_ACK ; 
 int /*<<< orphan*/  IEEE80211_FC0_TYPE_CTL ; 
 int /*<<< orphan*/  S_SEND_FRAG ; 
 int /*<<< orphan*/  S_START ; 
 int /*<<< orphan*/  S_WAIT_RELAY ; 
 int elapsed (struct timeval*,struct timeval*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  frame_type (struct ieee80211_frame*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ieee80211_frame* get_wifi (char*,int*) ; 
 int gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int select (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  send_packet (struct params*) ; 
 int sniff (scalar_t__,char*,int) ; 

void wait_ack(struct params *p)
{
	struct timeval now;
	int el;
	int tout = 10*1000;
	fd_set fds;
	int rc;
	char buf[4096];
	struct ieee80211_frame *wh;

	if (gettimeofday(&now, NULL) == -1)
		err(1, "gettimeofday()");

	/* check for timeout */
	el = elapsed(&p->last, &now);
	if (el >= tout) {
		if (p->data_try >= 3) {
#if 0		
			printf("Re-sending whole lot\n");
#endif			
			p->state = S_START;
			return;
		}
#if 0
		printf("Re-sending frag\n");
#endif		
		send_packet(p);
		el = 0;
	}

	el = tout - el;
	now.tv_sec = el/1000/1000;
	now.tv_usec = el - now.tv_sec*1000*1000;

	FD_ZERO(&fds);
	FD_SET(p->rx, &fds);
	if (select(p->rx+1, &fds, NULL, NULL, &now) == -1)
		err(1, "select()");

	if (!FD_ISSET(p->rx, &fds))
		return;

	/* grab ack */
        rc = sniff(p->rx, buf, sizeof(buf));
        if (rc == -1)
                err(1, "sniff()");

        wh = get_wifi(buf, &rc);
        if (!wh)
                return;

	if (!frame_type(wh, IEEE80211_FC0_TYPE_CTL, IEEE80211_FC0_SUBTYPE_ACK))
		return;

	if (memcmp(p->mac, wh->i_addr1, 6) != 0)
		return;

	/* wait for relay */
	if (p->frag == 0) {
		p->state = S_WAIT_RELAY;
		if (gettimeofday(&p->last, NULL) == -1)
			err(1, "gettimeofday()");
	}
	else
		p->state = S_SEND_FRAG;
}