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
struct params {int /*<<< orphan*/  mac; } ;
struct ieee80211_frame {int /*<<< orphan*/  i_addr2; int /*<<< orphan*/  i_addr1; } ;

/* Variables and functions */
 int le16toh (unsigned short) ; 
 int /*<<< orphan*/  mac2str (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  send_auth (struct params*,int /*<<< orphan*/ ) ; 

void read_auth(struct params *p, struct ieee80211_frame *wh, int len)
{
	unsigned short *ptr;
	char mac[6*3];

	if (memcmp(wh->i_addr1, p->mac, 6) != 0)
		return;

	ptr = (unsigned short*) (wh+1);
	if (le16toh(*ptr) != 0) {
		printf("Unknown auth algo %d\n", le16toh(*ptr));
		return;
	}
	ptr++;
	if (le16toh(*ptr) == 1) {
		mac2str(mac, wh->i_addr2);
		printf("Got auth from %s\n", mac);
		send_auth(p, wh->i_addr2);
	} else {
		printf("Weird seq in auth %d\n", le16toh(*ptr));
	}
}