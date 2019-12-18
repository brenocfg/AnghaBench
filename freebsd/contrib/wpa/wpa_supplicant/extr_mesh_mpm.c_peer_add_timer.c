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
struct hostapd_data {int /*<<< orphan*/  mesh_required_peer; } ;
struct TYPE_2__ {struct hostapd_data** bss; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void peer_add_timer(void *eloop_ctx, void *user_data)
{
	struct wpa_supplicant *wpa_s = eloop_ctx;
	struct hostapd_data *hapd = wpa_s->ifmsh->bss[0];

	os_memset(hapd->mesh_required_peer, 0, ETH_ALEN);
}