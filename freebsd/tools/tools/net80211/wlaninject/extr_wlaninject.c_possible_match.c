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
struct ieee80211_frame {int* i_fc; int /*<<< orphan*/  i_addr3; int /*<<< orphan*/  i_addr2; int /*<<< orphan*/  i_addr1; } ;

/* Variables and functions */
 int IEEE80211_FC0_SUBTYPE_MASK ; 
 int IEEE80211_FC0_TYPE_CTL ; 
 int IEEE80211_FC0_TYPE_MASK ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

int possible_match(struct ieee80211_frame *sent, int slen,
		   struct ieee80211_frame *got, int glen)
{
	if (slen != glen)
		return 0;

	if (memcmp(sent->i_addr1, got->i_addr1, 6) != 0)
		printf("Addr1 doesn't match\n");

	if ((sent->i_fc[0] & IEEE80211_FC0_TYPE_MASK) !=
	    (got->i_fc[0] & IEEE80211_FC0_TYPE_MASK))
		return 0;

	if ((sent->i_fc[0] & IEEE80211_FC0_SUBTYPE_MASK) !=
	    (got->i_fc[0] & IEEE80211_FC0_SUBTYPE_MASK))
		return 0;

	/* Good enough for CTL frames I guess */
	if ((got->i_fc[0] & IEEE80211_FC0_TYPE_MASK) == IEEE80211_FC0_TYPE_CTL)
		return 1;

	if (memcmp(sent->i_addr2, got->i_addr2, 6) == 0 &&
	    memcmp(sent->i_addr3, got->i_addr3, 6) == 0)
	    	return 1;

	return 0;
}