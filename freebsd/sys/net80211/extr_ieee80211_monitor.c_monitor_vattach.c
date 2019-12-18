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
struct ieee80211vap {int /*<<< orphan*/  iv_opdetach; int /*<<< orphan*/  iv_input; int /*<<< orphan*/  iv_newstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  monitor_input ; 
 int /*<<< orphan*/  monitor_newstate ; 
 int /*<<< orphan*/  monitor_vdetach ; 

__attribute__((used)) static void
monitor_vattach(struct ieee80211vap *vap)
{
	vap->iv_newstate = monitor_newstate;
	vap->iv_input = monitor_input;
	vap->iv_opdetach = monitor_vdetach;
}