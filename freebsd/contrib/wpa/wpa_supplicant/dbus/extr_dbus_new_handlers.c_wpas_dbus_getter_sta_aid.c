#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wpa_dbus_property_desc {int dummy; } ;
struct sta_info {int /*<<< orphan*/  aid; } ;
struct sta_handler_args {int /*<<< orphan*/  sta; TYPE_2__* wpa_s; } ;
typedef  int /*<<< orphan*/  dbus_bool_t ;
struct TYPE_4__ {TYPE_1__* ap_iface; } ;
struct TYPE_3__ {int /*<<< orphan*/ * bss; } ;
typedef  int /*<<< orphan*/  DBusMessageIter ;
typedef  int /*<<< orphan*/  DBusError ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_TYPE_UINT16 ; 
 int /*<<< orphan*/  FALSE ; 
 struct sta_info* ap_get_sta (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpas_dbus_simple_property_getter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

dbus_bool_t wpas_dbus_getter_sta_aid(
	const struct wpa_dbus_property_desc *property_desc,
	DBusMessageIter *iter, DBusError *error, void *user_data)
{
#ifdef CONFIG_AP
	struct sta_handler_args *args = user_data;
	struct sta_info *sta;

	sta = ap_get_sta(args->wpa_s->ap_iface->bss[0], args->sta);
	if (!sta)
		return FALSE;

	return wpas_dbus_simple_property_getter(iter, DBUS_TYPE_UINT16,
						&sta->aid,
						error);
#else /* CONFIG_AP */
    return FALSE;
#endif /* CONFIG_AP */
}