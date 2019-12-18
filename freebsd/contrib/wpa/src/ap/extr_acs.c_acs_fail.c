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
struct hostapd_iface {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  acs_cleanup (struct hostapd_iface*) ; 
 int /*<<< orphan*/  hostapd_disable_iface (struct hostapd_iface*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void acs_fail(struct hostapd_iface *iface)
{
	wpa_printf(MSG_ERROR, "ACS: Failed to start");
	acs_cleanup(iface);
	hostapd_disable_iface(iface);
}