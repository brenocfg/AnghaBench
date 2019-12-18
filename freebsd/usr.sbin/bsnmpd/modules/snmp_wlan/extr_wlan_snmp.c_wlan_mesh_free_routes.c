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
struct wlan_mesh_route {int dummy; } ;
struct wlan_iface {int /*<<< orphan*/  mesh_routelist; } ;

/* Variables and functions */
 struct wlan_mesh_route* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct wlan_mesh_route*) ; 
 int /*<<< orphan*/  wr ; 

__attribute__((used)) static void
wlan_mesh_free_routes(struct wlan_iface *wif)
{
	struct wlan_mesh_route *wmr;

	while ((wmr = SLIST_FIRST(&wif->mesh_routelist)) != NULL) {
		SLIST_REMOVE_HEAD(&wif->mesh_routelist, wr);
		free(wmr);
	}

	SLIST_INIT(&wif->mesh_routelist);
}