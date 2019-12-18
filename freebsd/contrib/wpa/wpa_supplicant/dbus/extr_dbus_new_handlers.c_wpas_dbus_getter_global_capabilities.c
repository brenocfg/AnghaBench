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
struct wpa_supplicant {struct wpa_supplicant* next; } ;
struct wpa_global {struct wpa_supplicant* ifaces; } ;
struct wpa_dbus_property_desc {int dummy; } ;
typedef  int /*<<< orphan*/  dbus_bool_t ;
typedef  int /*<<< orphan*/  DBusMessageIter ;
typedef  int /*<<< orphan*/  DBusError ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_TYPE_STRING ; 
 scalar_t__ wpa_is_fils_sk_pfs_supported (struct wpa_supplicant*) ; 
 scalar_t__ wpa_is_fils_supported (struct wpa_supplicant*) ; 
 int /*<<< orphan*/  wpas_dbus_simple_array_property_getter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const**,size_t,int /*<<< orphan*/ *) ; 

dbus_bool_t wpas_dbus_getter_global_capabilities(
	const struct wpa_dbus_property_desc *property_desc,
	DBusMessageIter *iter, DBusError *error, void *user_data)
{
	const char *capabilities[10] = { NULL, NULL, NULL, NULL, NULL, NULL,
					NULL, NULL, NULL, NULL };
	size_t num_items = 0;
#ifdef CONFIG_FILS
	struct wpa_global *global = user_data;
	struct wpa_supplicant *wpa_s;
	int fils_supported = 0, fils_sk_pfs_supported = 0;

	for (wpa_s = global->ifaces; wpa_s; wpa_s = wpa_s->next) {
		if (wpa_is_fils_supported(wpa_s))
			fils_supported = 1;
		if (wpa_is_fils_sk_pfs_supported(wpa_s))
			fils_sk_pfs_supported = 1;
	}
#endif /* CONFIG_FILS */

#ifdef CONFIG_AP
	capabilities[num_items++] = "ap";
#endif /* CONFIG_AP */
#ifdef CONFIG_IBSS_RSN
	capabilities[num_items++] = "ibss-rsn";
#endif /* CONFIG_IBSS_RSN */
#ifdef CONFIG_P2P
	capabilities[num_items++] = "p2p";
#endif /* CONFIG_P2P */
#ifdef CONFIG_INTERWORKING
	capabilities[num_items++] = "interworking";
#endif /* CONFIG_INTERWORKING */
#ifdef CONFIG_IEEE80211W
	capabilities[num_items++] = "pmf";
#endif /* CONFIG_IEEE80211W */
#ifdef CONFIG_MESH
	capabilities[num_items++] = "mesh";
#endif /* CONFIG_MESH */
#ifdef CONFIG_FILS
	if (fils_supported)
		capabilities[num_items++] = "fils";
	if (fils_sk_pfs_supported)
		capabilities[num_items++] = "fils_sk_pfs";
#endif /* CONFIG_FILS */
#ifdef CONFIG_IEEE80211R
	capabilities[num_items++] = "ft";
#endif /* CONFIG_IEEE80211R */
#ifdef CONFIG_SHA384
	capabilities[num_items++] = "sha384";
#endif /* CONFIG_SHA384 */

	return wpas_dbus_simple_array_property_getter(iter,
						      DBUS_TYPE_STRING,
						      capabilities,
						      num_items, error);
}