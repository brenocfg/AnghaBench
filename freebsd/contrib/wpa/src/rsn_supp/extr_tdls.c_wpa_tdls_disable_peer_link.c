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
struct wpa_tdls_peer {int /*<<< orphan*/  addr; } ;
struct wpa_sm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TDLS_DISABLE_LINK ; 
 int /*<<< orphan*/  wpa_sm_tdls_oper (struct wpa_sm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_tdls_peer_free (struct wpa_sm*,struct wpa_tdls_peer*) ; 

__attribute__((used)) static void wpa_tdls_disable_peer_link(struct wpa_sm *sm,
				       struct wpa_tdls_peer *peer)
{
	wpa_sm_tdls_oper(sm, TDLS_DISABLE_LINK, peer->addr);
	wpa_tdls_peer_free(sm, peer);
}