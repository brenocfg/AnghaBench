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
struct params {int /*<<< orphan*/  ap; int /*<<< orphan*/  mac; int /*<<< orphan*/  rx; } ;
struct ieee80211_frame {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_FC0_SUBTYPE_AUTH ; 
 int /*<<< orphan*/  IEEE80211_FC0_TYPE_MGT ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  for_me (struct ieee80211_frame*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frame_type (struct ieee80211_frame*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  from_ap (struct ieee80211_frame*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_process (struct ieee80211_frame*,struct params*,int) ; 
 struct ieee80211_frame* get_wifi (char*,int*) ; 
 int le16toh (short) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int sniff (int /*<<< orphan*/ ,char*,int) ; 

int get_auth(struct params *p)
{
	char buf[4096];
	int rc;
	struct ieee80211_frame *wh;
	short *data;

	rc = sniff(p->rx, buf, sizeof(buf));
	if (rc == -1)
		err(1, "sniff()");

	wh = get_wifi(buf, &rc);
	if (!wh)
		return 0;

	generic_process(wh, p, rc);

	if (!for_me(wh, p->mac))
		return 0;

	if (!from_ap(wh, p->ap))
		return 0;

	if (!frame_type(wh, IEEE80211_FC0_TYPE_MGT,
			IEEE80211_FC0_SUBTYPE_AUTH))
		return 0;

	data = (short*) (wh+1);
	
	/* algo */
	if (le16toh(*data) != 0) {
		printf("Not open-system %d!\n", le16toh(*data));
		return 0;
	}
	data++;
	
	/* transaction no. */
	if (le16toh(*data) != 2) {
		printf("Got transaction %d!\n", le16toh(*data));
		return 0;
	}
	data++;

	/* status code */
	rc = le16toh(*data);
	if (rc == 0) {
		printf("Authenticated\n");
		return 1;
	}

	printf("Authentication failed code=%d\n", rc);
	return 0;
}