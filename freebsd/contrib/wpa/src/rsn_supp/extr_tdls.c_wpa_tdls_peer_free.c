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
struct wpa_tdls_peer {int dummy; } ;
struct wpa_sm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (struct wpa_tdls_peer*) ; 
 int /*<<< orphan*/  wpa_tdls_peer_clear (struct wpa_sm*,struct wpa_tdls_peer*) ; 
 int /*<<< orphan*/  wpa_tdls_peer_remove_from_list (struct wpa_sm*,struct wpa_tdls_peer*) ; 

__attribute__((used)) static void wpa_tdls_peer_free(struct wpa_sm *sm, struct wpa_tdls_peer *peer)
{
	wpa_tdls_peer_clear(sm, peer);
	wpa_tdls_peer_remove_from_list(sm, peer);
	os_free(peer);
}