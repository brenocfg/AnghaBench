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
struct mesh_conf {scalar_t__ mesh_pp_id; scalar_t__ mesh_pm_id; scalar_t__ mesh_cc_id; scalar_t__ mesh_sp_id; scalar_t__ mesh_auth_id; int /*<<< orphan*/  meshid; int /*<<< orphan*/  meshid_len; } ;
struct ieee802_11_elems {int mesh_config_len; scalar_t__* mesh_config; int /*<<< orphan*/  mesh_id_len; int /*<<< orphan*/  mesh_id; } ;
struct TYPE_2__ {struct mesh_conf* mconf; } ;
typedef  int Boolean ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Boolean matches_local(struct wpa_supplicant *wpa_s,
			     struct ieee802_11_elems *elems)
{
	struct mesh_conf *mconf = wpa_s->ifmsh->mconf;

	if (elems->mesh_config_len < 5)
		return FALSE;

	return (mconf->meshid_len == elems->mesh_id_len &&
		os_memcmp(mconf->meshid, elems->mesh_id,
			  elems->mesh_id_len) == 0 &&
		mconf->mesh_pp_id == elems->mesh_config[0] &&
		mconf->mesh_pm_id == elems->mesh_config[1] &&
		mconf->mesh_cc_id == elems->mesh_config[2] &&
		mconf->mesh_sp_id == elems->mesh_config[3] &&
		mconf->mesh_auth_id == elems->mesh_config[4]);
}