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
struct wpa_supplicant {int /*<<< orphan*/  mesh_rsn; } ;
struct sta_info {int /*<<< orphan*/  peer_nonce; int /*<<< orphan*/  my_nonce; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  WPA_NONCE_LEN ; 
 int /*<<< orphan*/  mesh_rsn_derive_aek (int /*<<< orphan*/ ,struct sta_info*) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ random_get_bytes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

void mesh_rsn_init_ampe_sta(struct wpa_supplicant *wpa_s, struct sta_info *sta)
{
	if (random_get_bytes(sta->my_nonce, WPA_NONCE_LEN) < 0) {
		wpa_printf(MSG_INFO, "mesh: Failed to derive random nonce");
		/* TODO: How to handle this more cleanly? */
	}
	os_memset(sta->peer_nonce, 0, WPA_NONCE_LEN);
	mesh_rsn_derive_aek(wpa_s->mesh_rsn, sta);
}