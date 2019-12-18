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
struct hostapd_iface {TYPE_1__* interfaces; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* for_each_interface ) (TYPE_1__*,int /*<<< orphan*/  (*) (struct hostapd_iface*,int /*<<< orphan*/ *),int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  hostapd_owe_iface_iter2 (struct hostapd_iface*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/  (*) (struct hostapd_iface*,int /*<<< orphan*/ *),int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hostapd_owe_update_trans(struct hostapd_iface *iface)
{
#ifdef CONFIG_OWE
	/* Check whether the enabled BSS can complete OWE transition mode
	 * configuration for any pending interface. */
	if (!iface->interfaces ||
	    !iface->interfaces->for_each_interface)
		hostapd_owe_iface_iter2(iface, NULL);
	else
		iface->interfaces->for_each_interface(
			iface->interfaces, hostapd_owe_iface_iter2, NULL);
#endif /* CONFIG_OWE */
}