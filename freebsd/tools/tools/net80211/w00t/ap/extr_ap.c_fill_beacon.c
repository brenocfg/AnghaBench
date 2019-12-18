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
struct params {int /*<<< orphan*/  chan; int /*<<< orphan*/  ssid; } ;
struct ieee80211_frame {int dummy; } ;

/* Variables and functions */
 char IEEE80211_CAPINFO_ESS ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int strlen (int /*<<< orphan*/ ) ; 

int fill_beacon(struct params *p, struct ieee80211_frame *wh)
{
	int len;
	char *ptr;

	ptr = (char*) (wh+1);
	ptr += 8; /* timestamp */
	ptr += 2; /* bint */
	*ptr |= IEEE80211_CAPINFO_ESS;
	ptr += 2; /* capa */

	/* ssid */
	len = strlen(p->ssid);
	*ptr++ = 0;
	*ptr++ = len;
	memcpy(ptr, p->ssid, len);
	ptr += len;

	/* rates */
        *ptr++ = 1;
        *ptr++ = 4;
        *ptr++ = 2 | 0x80;
        *ptr++ = 4 | 0x80;
        *ptr++ = 11;
        *ptr++ = 22;

	/* ds param */
	*ptr++ = 3;
	*ptr++ = 1;
	*ptr++ = p->chan;
	
	return ptr - ((char*) wh);
}