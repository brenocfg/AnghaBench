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
 int /*<<< orphan*/  rum_cmd_sleepable (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rum_update_slot_cb ; 

__attribute__((used)) static void
rum_update_slot(struct ieee80211com *ic)
{
	rum_cmd_sleepable(ic->ic_softc, NULL, 0, 0, rum_update_slot_cb);
}