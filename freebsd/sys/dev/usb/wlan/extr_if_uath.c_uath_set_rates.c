#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct uath_softc {int dummy; } ;
struct uath_cmd_rateset {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * set; int /*<<< orphan*/  length; } ;
struct uath_cmd_rates {TYPE_1__ rateset; void* size; void* connid; } ;
struct ieee80211_rateset {int /*<<< orphan*/  rs_nrates; int /*<<< orphan*/  rs_rates; } ;
typedef  int /*<<< orphan*/  rates ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (struct uath_softc*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UATH_DEBUG_RATES ; 
 int UATH_ID_BSS ; 
 int /*<<< orphan*/  WDCMSG_SET_BASIC_RATE ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* htobe32 (int) ; 
 int /*<<< orphan*/  memset (struct uath_cmd_rates*,int /*<<< orphan*/ ,int) ; 
 int uath_cmd_write (struct uath_softc*,int /*<<< orphan*/ ,struct uath_cmd_rates*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
uath_set_rates(struct uath_softc *sc, const struct ieee80211_rateset *rs)
{
	struct uath_cmd_rates rates;

	memset(&rates, 0, sizeof(rates));
	rates.connid = htobe32(UATH_ID_BSS);		/* XXX */
	rates.size   = htobe32(sizeof(struct uath_cmd_rateset));
	/* XXX bounds check rs->rs_nrates */
	rates.rateset.length = rs->rs_nrates;
	bcopy(rs->rs_rates, &rates.rateset.set[0], rs->rs_nrates);

	DPRINTF(sc, UATH_DEBUG_RATES,
	    "setting supported rates nrates=%d\n", rs->rs_nrates);
	return uath_cmd_write(sc, WDCMSG_SET_BASIC_RATE,
	    &rates, sizeof rates, 0);
}