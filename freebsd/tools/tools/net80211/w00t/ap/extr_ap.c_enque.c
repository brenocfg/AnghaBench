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
struct params {int packet_len; int packet_try; int /*<<< orphan*/  plast; scalar_t__ packet; } ;
struct ieee80211_frame {int /*<<< orphan*/ * i_fc; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_FC1_RETRY ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ broadcast (struct ieee80211_frame*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int gettimeofday (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,struct ieee80211_frame*,int) ; 

void enque(struct params *p, struct ieee80211_frame *wh, int len)
{
	if (broadcast(wh))
		return;

	assert(sizeof(p->packet) >= len);

	memcpy(p->packet, wh, len);
	p->packet_len = len;
	p->packet_try = 1;

	wh = (struct ieee80211_frame*) p->packet;
	wh->i_fc[1] |= IEEE80211_FC1_RETRY;

	if (gettimeofday(&p->plast, NULL) == -1)
		err(1, "gettimeofday()");
}