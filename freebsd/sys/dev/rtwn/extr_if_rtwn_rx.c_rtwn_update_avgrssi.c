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
struct rtwn_softc {int dummy; } ;
struct rtwn_node {int avg_pwdb; int /*<<< orphan*/  id; } ;
typedef  int int8_t ;

/* Variables and functions */
 int /*<<< orphan*/  RTWN_DEBUG_RSSI ; 
 int /*<<< orphan*/  RTWN_DPRINTF (struct rtwn_softc*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
rtwn_update_avgrssi(struct rtwn_softc *sc, struct rtwn_node *un, int8_t rssi,
    int is_cck)
{
	int pwdb;

	/* Convert antenna signal to percentage. */
	if (rssi <= -100 || rssi >= 20)
		pwdb = 0;
	else if (rssi >= 0)
		pwdb = 100;
	else
		pwdb = 100 + rssi;
	if (is_cck) {
		/* CCK gain is smaller than OFDM/MCS gain. */
		pwdb += 6;
		if (pwdb > 100)
			pwdb = 100;
		if (pwdb <= 14)
			pwdb -= 4;
		else if (pwdb <= 26)
			pwdb -= 8;
		else if (pwdb <= 34)
			pwdb -= 6;
		else if (pwdb <= 42)
			pwdb -= 2;
	}

	if (un->avg_pwdb == -1)	/* Init. */
		un->avg_pwdb = pwdb;
	else if (un->avg_pwdb < pwdb)
		un->avg_pwdb = ((un->avg_pwdb * 19 + pwdb) / 20) + 1;
	else
		un->avg_pwdb = ((un->avg_pwdb * 19 + pwdb) / 20);

	RTWN_DPRINTF(sc, RTWN_DEBUG_RSSI,
	    "MACID %d, PWDB %d, EMA %d\n", un->id, pwdb, un->avg_pwdb);
}