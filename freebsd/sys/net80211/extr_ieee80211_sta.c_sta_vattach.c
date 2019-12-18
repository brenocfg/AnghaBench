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
struct ieee80211vap {int /*<<< orphan*/  iv_bmiss; int /*<<< orphan*/  iv_opdetach; int /*<<< orphan*/  iv_recv_ctl; int /*<<< orphan*/  iv_recv_mgmt; int /*<<< orphan*/  iv_input; int /*<<< orphan*/  iv_newstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  sta_beacon_miss ; 
 int /*<<< orphan*/  sta_input ; 
 int /*<<< orphan*/  sta_newstate ; 
 int /*<<< orphan*/  sta_recv_ctl ; 
 int /*<<< orphan*/  sta_recv_mgmt ; 
 int /*<<< orphan*/  sta_vdetach ; 

__attribute__((used)) static void
sta_vattach(struct ieee80211vap *vap)
{
	vap->iv_newstate = sta_newstate;
	vap->iv_input = sta_input;
	vap->iv_recv_mgmt = sta_recv_mgmt;
	vap->iv_recv_ctl = sta_recv_ctl;
	vap->iv_opdetach = sta_vdetach;
	vap->iv_bmiss = sta_beacon_miss;
}