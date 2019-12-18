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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 char IEEE80211_FC0_SUBTYPE_ACK ; 
 char IEEE80211_FC0_TYPE_CTL ; 
 int inject (int,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 

int send_ack(int fd, char *mac)
{
	static char buf[2+2+6];
	static char *p = 0;
	int rc;

	if (!p) {
		memset(buf, 0, sizeof(buf));
		buf[0] |= IEEE80211_FC0_TYPE_CTL | IEEE80211_FC0_SUBTYPE_ACK;
		p = &buf[4];
	}

	memcpy(p, mac, 6);

	rc = inject(fd, buf, sizeof(buf));
	return rc;
}