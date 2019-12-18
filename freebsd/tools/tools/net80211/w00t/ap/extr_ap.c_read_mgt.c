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
struct ieee80211_frame {int* i_fc; } ;

/* Variables and functions */
#define  IEEE80211_FC0_SUBTYPE_ASSOC_REQ 133 
#define  IEEE80211_FC0_SUBTYPE_ASSOC_RESP 132 
#define  IEEE80211_FC0_SUBTYPE_AUTH 131 
#define  IEEE80211_FC0_SUBTYPE_BEACON 130 
 int IEEE80211_FC0_SUBTYPE_MASK ; 
#define  IEEE80211_FC0_SUBTYPE_PROBE_REQ 129 
#define  IEEE80211_FC0_SUBTYPE_PROBE_RESP 128 
 int IEEE80211_FC0_SUBTYPE_SHIFT ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  read_assoc (struct params*,struct ieee80211_frame*,int) ; 
 int /*<<< orphan*/  read_auth (struct params*,struct ieee80211_frame*,int) ; 
 int /*<<< orphan*/  read_preq (struct params*,struct ieee80211_frame*,int) ; 

void read_mgt(struct params *p, struct ieee80211_frame *wh, int len)
{
	switch (wh->i_fc[0] & IEEE80211_FC0_SUBTYPE_MASK) {
	case IEEE80211_FC0_SUBTYPE_PROBE_REQ:
		read_preq(p, wh, len);
		break;
		
	case IEEE80211_FC0_SUBTYPE_PROBE_RESP:
		break;

	case IEEE80211_FC0_SUBTYPE_AUTH:
		read_auth(p, wh, len);
		break;

	case IEEE80211_FC0_SUBTYPE_ASSOC_REQ:
		read_assoc(p, wh, len);
		break;

	case IEEE80211_FC0_SUBTYPE_ASSOC_RESP:
	case IEEE80211_FC0_SUBTYPE_BEACON:
		break;

	default:
		printf("wtf %d\n", (wh->i_fc[0] & IEEE80211_FC0_SUBTYPE_MASK) >>
				   IEEE80211_FC0_SUBTYPE_SHIFT);
		abort();
		break;
	}
}