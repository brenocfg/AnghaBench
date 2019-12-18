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
typedef  int /*<<< orphan*/  uint8_t ;
struct ieee80211com {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDSHORT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IEEE80211_ELEMID_CFPARMS ; 

__attribute__((used)) static uint8_t *
ieee80211_add_cfparms(uint8_t *frm, struct ieee80211com *ic)
{
#define	ADDSHORT(frm, v) do {	\
	le16enc(frm, v);	\
	frm += 2;		\
} while (0)
	*frm++ = IEEE80211_ELEMID_CFPARMS;
	*frm++ = 6;
	*frm++ = 0;		/* CFP count */
	*frm++ = 2;		/* CFP period */
	ADDSHORT(frm, 0);	/* CFP MaxDuration (TU) */
	ADDSHORT(frm, 0);	/* CFP CurRemaining (TU) */
	return frm;
#undef ADDSHORT
}