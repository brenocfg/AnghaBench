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
struct ieee80211com {int /*<<< orphan*/  ic_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  wi_write_multi (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
wi_update_mcast(struct ieee80211com *ic)
{

	wi_write_multi(ic->ic_softc);
}