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
struct wpa_supplicant {TYPE_1__* ifmsh; } ;
struct sta_info {int dummy; } ;
struct mesh_conf {int dot11MeshRetryTimeout; } ;
typedef  enum mesh_plink_state { ____Placeholder_mesh_plink_state } mesh_plink_state ;
struct TYPE_2__ {struct mesh_conf* mconf; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLINK_OPEN ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct wpa_supplicant*,struct sta_info*) ; 
 int /*<<< orphan*/  eloop_register_timeout (int,int,int /*<<< orphan*/ ,struct wpa_supplicant*,struct sta_info*) ; 
 int /*<<< orphan*/  mesh_mpm_send_plink_action (struct wpa_supplicant*,struct sta_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plink_timer ; 
 int /*<<< orphan*/  wpa_mesh_set_plink_state (struct wpa_supplicant*,struct sta_info*,int) ; 

__attribute__((used)) static void
mesh_mpm_plink_open(struct wpa_supplicant *wpa_s, struct sta_info *sta,
		    enum mesh_plink_state next_state)
{
	struct mesh_conf *conf = wpa_s->ifmsh->mconf;

	eloop_cancel_timeout(plink_timer, wpa_s, sta);
	eloop_register_timeout(conf->dot11MeshRetryTimeout / 1000,
			       (conf->dot11MeshRetryTimeout % 1000) * 1000,
			       plink_timer, wpa_s, sta);
	mesh_mpm_send_plink_action(wpa_s, sta, PLINK_OPEN, 0);
	wpa_mesh_set_plink_state(wpa_s, sta, next_state);
}