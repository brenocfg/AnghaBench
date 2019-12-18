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
struct hostapd_data {TYPE_1__* iface; } ;
struct hapd_interfaces {struct dynamic_iface* vlan_priv; } ;
struct dynamic_iface {int usage; int clean; struct dynamic_iface* next; int /*<<< orphan*/  ifname; } ;
struct TYPE_2__ {struct hapd_interfaces* interfaces; } ;

/* Variables and functions */
 scalar_t__ os_strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 struct dynamic_iface* os_zalloc (int) ; 

__attribute__((used)) static void dyn_iface_get(struct hostapd_data *hapd, const char *ifname,
			  int clean)
{
	struct dynamic_iface *next, **dynamic_ifaces;
	struct hapd_interfaces *interfaces;

	interfaces = hapd->iface->interfaces;
	dynamic_ifaces = &interfaces->vlan_priv;

	for (next = *dynamic_ifaces; next; next = next->next) {
		if (os_strcmp(ifname, next->ifname) == 0)
			break;
	}

	if (next) {
		next->usage++;
		next->clean |= clean;
		return;
	}

	if (!clean)
		return;

	next = os_zalloc(sizeof(*next));
	if (!next)
		return;
	os_strlcpy(next->ifname, ifname, sizeof(next->ifname));
	next->usage = 1;
	next->clean = clean;
	next->next = *dynamic_ifaces;
	*dynamic_ifaces = next;
}