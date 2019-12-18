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
struct wlan_iface {int /*<<< orphan*/  wname; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct wlan_iface* wlan_first_interface () ; 
 struct wlan_iface* wlan_next_interface (struct wlan_iface*) ; 

__attribute__((used)) static void
wlan_dump(void)
{
	/* XXX: Print some debug info to syslog. */
	struct wlan_iface *wif;

	for (wif = wlan_first_interface(); wif != NULL;
	    wif = wlan_next_interface(wif))
		syslog(LOG_ERR, "wlan iface %s", wif->wname);
}