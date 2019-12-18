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
struct wpa_supplicant {unsigned int mesh_if_created; int /*<<< orphan*/  ifname; struct wpa_supplicant* next; struct wpa_supplicant* parent; } ;
struct wpa_global {struct wpa_supplicant* p2p_invite_group; struct wpa_supplicant* p2p_group_formation; struct wpa_supplicant* ifaces; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  WPA_IF_MESH ; 
 int /*<<< orphan*/  os_free (char*) ; 
 char* os_strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_dbg (struct wpa_supplicant*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpa_drv_if_remove (struct wpa_supplicant*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_supplicant_deinit_iface (struct wpa_supplicant*,int,int) ; 

int wpa_supplicant_remove_iface(struct wpa_global *global,
				struct wpa_supplicant *wpa_s,
				int terminate)
{
	struct wpa_supplicant *prev;
#ifdef CONFIG_MESH
	unsigned int mesh_if_created = wpa_s->mesh_if_created;
	char *ifname = NULL;
	struct wpa_supplicant *parent = wpa_s->parent;
#endif /* CONFIG_MESH */

	/* Remove interface from the global list of interfaces */
	prev = global->ifaces;
	if (prev == wpa_s) {
		global->ifaces = wpa_s->next;
	} else {
		while (prev && prev->next != wpa_s)
			prev = prev->next;
		if (prev == NULL)
			return -1;
		prev->next = wpa_s->next;
	}

	wpa_dbg(wpa_s, MSG_DEBUG, "Removing interface %s", wpa_s->ifname);

#ifdef CONFIG_MESH
	if (mesh_if_created) {
		ifname = os_strdup(wpa_s->ifname);
		if (ifname == NULL) {
			wpa_dbg(wpa_s, MSG_ERROR,
				"mesh: Failed to malloc ifname");
			return -1;
		}
	}
#endif /* CONFIG_MESH */

	if (global->p2p_group_formation == wpa_s)
		global->p2p_group_formation = NULL;
	if (global->p2p_invite_group == wpa_s)
		global->p2p_invite_group = NULL;
	wpa_supplicant_deinit_iface(wpa_s, 1, terminate);

#ifdef CONFIG_MESH
	if (mesh_if_created) {
		wpa_drv_if_remove(parent, WPA_IF_MESH, ifname);
		os_free(ifname);
	}
#endif /* CONFIG_MESH */

	return 0;
}