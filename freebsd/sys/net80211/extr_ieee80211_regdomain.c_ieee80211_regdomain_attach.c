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
struct TYPE_2__ {scalar_t__ regdomain; scalar_t__ country; char location; } ;
struct ieee80211com {int /*<<< orphan*/  ic_setregdomain; int /*<<< orphan*/  ic_getradiocaps; TYPE_1__ ic_regdomain; } ;

/* Variables and functions */
 scalar_t__ CTRY_DEFAULT ; 
 int /*<<< orphan*/  null_getradiocaps ; 
 int /*<<< orphan*/  null_setregdomain ; 

void
ieee80211_regdomain_attach(struct ieee80211com *ic)
{
	if (ic->ic_regdomain.regdomain == 0 &&
	    ic->ic_regdomain.country == CTRY_DEFAULT) {
		ic->ic_regdomain.location = ' ';		/* both */
		/* NB: driver calls ieee80211_init_channels or similar */
	}
	ic->ic_getradiocaps = null_getradiocaps;
	ic->ic_setregdomain = null_setregdomain;
}