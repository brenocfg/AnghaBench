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
struct upnp_wps_peer {scalar_t__ wps; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  dl_list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (struct upnp_wps_peer*) ; 
 int /*<<< orphan*/  wps_deinit (scalar_t__) ; 

__attribute__((used)) static void wps_upnp_peer_del(struct upnp_wps_peer *peer)
{
	dl_list_del(&peer->list);
	if (peer->wps)
		wps_deinit(peer->wps);
	os_free(peer);
}