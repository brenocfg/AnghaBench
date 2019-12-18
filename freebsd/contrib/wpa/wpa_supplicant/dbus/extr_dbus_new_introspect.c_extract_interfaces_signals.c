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
struct wpa_dbus_signal_desc {int /*<<< orphan*/  args; scalar_t__ dbus_signal; int /*<<< orphan*/  dbus_interface; } ;
struct interfaces {int /*<<< orphan*/  xml; } ;
struct dl_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_entry (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct interfaces* add_interface (struct dl_list*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void extract_interfaces_signals(
	struct dl_list *list, const struct wpa_dbus_signal_desc *signals)
{
	const struct wpa_dbus_signal_desc *dsc;
	struct interfaces *iface;

	for (dsc = signals; dsc && dsc->dbus_signal; dsc++) {
		iface = add_interface(list, dsc->dbus_interface);
		if (iface)
			add_entry(iface->xml, "signal", dsc->dbus_signal,
				  dsc->args, 0);
	}
}