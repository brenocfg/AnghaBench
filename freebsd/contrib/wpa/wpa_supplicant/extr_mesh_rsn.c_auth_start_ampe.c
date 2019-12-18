#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sta_info {int dummy; } ;
struct mesh_rsn {TYPE_3__* wpa_s; } ;
struct hostapd_data {int dummy; } ;
struct TYPE_7__ {TYPE_2__* ifmsh; TYPE_1__* current_ssid; } ;
struct TYPE_6__ {struct hostapd_data** bss; } ;
struct TYPE_5__ {scalar_t__ mode; } ;

/* Variables and functions */
 scalar_t__ WPAS_MODE_MESH ; 
 struct sta_info* ap_get_sta (struct hostapd_data*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,TYPE_3__*,struct sta_info*) ; 
 int /*<<< orphan*/  mesh_auth_timer ; 
 int /*<<< orphan*/  mesh_mpm_auth_peer (TYPE_3__*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int auth_start_ampe(void *ctx, const u8 *addr)
{
	struct mesh_rsn *mesh_rsn = ctx;
	struct hostapd_data *hapd;
	struct sta_info *sta;

	if (mesh_rsn->wpa_s->current_ssid->mode != WPAS_MODE_MESH)
		return -1;

	hapd = mesh_rsn->wpa_s->ifmsh->bss[0];
	sta = ap_get_sta(hapd, addr);
	if (sta)
		eloop_cancel_timeout(mesh_auth_timer, mesh_rsn->wpa_s, sta);

	mesh_mpm_auth_peer(mesh_rsn->wpa_s, addr);
	return 0;
}