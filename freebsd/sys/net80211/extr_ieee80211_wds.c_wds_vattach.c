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
struct ieee80211vap {int /*<<< orphan*/  iv_opdetach; int /*<<< orphan*/  iv_recv_mgmt; int /*<<< orphan*/  iv_input; int /*<<< orphan*/  iv_newstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  wds_input ; 
 int /*<<< orphan*/  wds_newstate ; 
 int /*<<< orphan*/  wds_recv_mgmt ; 
 int /*<<< orphan*/  wds_vdetach ; 

__attribute__((used)) static void
wds_vattach(struct ieee80211vap *vap)
{
	vap->iv_newstate = wds_newstate;
	vap->iv_input = wds_input;
	vap->iv_recv_mgmt = wds_recv_mgmt;
	vap->iv_opdetach = wds_vdetach;
}