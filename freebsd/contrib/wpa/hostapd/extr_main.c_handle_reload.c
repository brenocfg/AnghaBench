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
struct hapd_interfaces {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  handle_reload_iface ; 
 int /*<<< orphan*/  hostapd_for_each_interface (struct hapd_interfaces*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void handle_reload(int sig, void *signal_ctx)
{
	struct hapd_interfaces *interfaces = signal_ctx;
	wpa_printf(MSG_DEBUG, "Signal %d received - reloading configuration",
		   sig);
	hostapd_for_each_interface(interfaces, handle_reload_iface, NULL);
}