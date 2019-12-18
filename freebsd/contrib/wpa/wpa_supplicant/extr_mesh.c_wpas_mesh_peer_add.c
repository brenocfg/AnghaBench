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
typedef  int /*<<< orphan*/  u8 ;
struct wpa_supplicant {int dummy; } ;

/* Variables and functions */
 int mesh_mpm_connect_peer (struct wpa_supplicant*,int /*<<< orphan*/  const*,int) ; 

int wpas_mesh_peer_add(struct wpa_supplicant *wpa_s, const u8 *addr,
		       int duration)
{
	return mesh_mpm_connect_peer(wpa_s, addr, duration);
}