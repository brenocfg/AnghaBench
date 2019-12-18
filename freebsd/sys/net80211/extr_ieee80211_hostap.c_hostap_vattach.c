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
struct ieee80211vap {int /*<<< orphan*/  iv_recv_pspoll; int /*<<< orphan*/  iv_deliver_data; int /*<<< orphan*/  iv_opdetach; int /*<<< orphan*/  iv_recv_ctl; int /*<<< orphan*/  iv_recv_mgmt; int /*<<< orphan*/  iv_input; int /*<<< orphan*/  iv_newstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  hostap_deliver_data ; 
 int /*<<< orphan*/  hostap_input ; 
 int /*<<< orphan*/  hostap_newstate ; 
 int /*<<< orphan*/  hostap_recv_ctl ; 
 int /*<<< orphan*/  hostap_recv_mgmt ; 
 int /*<<< orphan*/  hostap_vdetach ; 
 int /*<<< orphan*/  ieee80211_recv_pspoll ; 

__attribute__((used)) static void
hostap_vattach(struct ieee80211vap *vap)
{
	vap->iv_newstate = hostap_newstate;
	vap->iv_input = hostap_input;
	vap->iv_recv_mgmt = hostap_recv_mgmt;
	vap->iv_recv_ctl = hostap_recv_ctl;
	vap->iv_opdetach = hostap_vdetach;
	vap->iv_deliver_data = hostap_deliver_data;
	vap->iv_recv_pspoll = ieee80211_recv_pspoll;
}