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
struct ieee80211_frame {int* i_fc; int /*<<< orphan*/  i_addr2; } ;
struct client {int seq; int /*<<< orphan*/  mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_FC0_SUBTYPE_DATA ; 
 int /*<<< orphan*/  IEEE80211_FC0_TYPE_DATA ; 
 int IEEE80211_FC1_RETRY ; 
 struct client* client_find (struct params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  client_insert (struct params*,struct client*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  frame_type (struct ieee80211_frame*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac2str (char*,int /*<<< orphan*/ ) ; 
 struct client* malloc (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int seqno (struct ieee80211_frame*) ; 

int duplicate(struct params *p, struct ieee80211_frame *wh, int rc)
{
	struct client *c;
	int s;

	if (!frame_type(wh, IEEE80211_FC0_TYPE_DATA,
			IEEE80211_FC0_SUBTYPE_DATA))
		return 0;

	s = seqno(wh);

	c = client_find(p, wh->i_addr2);
	if (!c) {
		c = malloc(sizeof(*c));
		if (!c)
			err(1, "malloc()");

		memset(c, 0, sizeof(*c));
		memcpy(c->mac, wh->i_addr2, 6);

		c->seq = s-1;
		client_insert(p, c);
	}

	if (wh->i_fc[1] & IEEE80211_FC1_RETRY) {
		if ( (s <= c->seq) && ((c->seq - s ) < 5)) {
#if 0
			printf("Dup seq %d prev %d\n",
			       s, c->seq);
#endif
			return 1;
		}	
	}	

#if 0
	do {
		char mac[3*6];

		mac2str(mac, c->mac);
		printf("%s seq %d prev %d\n", mac, s, c->seq);
	} while (0);
#endif
	
	c->seq = s;
	return 0;
}