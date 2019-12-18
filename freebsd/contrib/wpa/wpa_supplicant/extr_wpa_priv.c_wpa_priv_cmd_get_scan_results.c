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
struct wpa_priv_interface {int /*<<< orphan*/  fd; TYPE_1__* driver; int /*<<< orphan*/ * drv_priv; } ;
struct sockaddr_un {int dummy; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;
struct TYPE_2__ {scalar_t__ get_scan_results2; } ;

/* Variables and functions */
 int /*<<< orphan*/  sendto (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_priv_get_scan_results2 (struct wpa_priv_interface*,struct sockaddr_un*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wpa_priv_cmd_get_scan_results(struct wpa_priv_interface *iface,
					  struct sockaddr_un *from,
					  socklen_t fromlen)
{
	if (iface->drv_priv == NULL)
		return;

	if (iface->driver->get_scan_results2)
		wpa_priv_get_scan_results2(iface, from, fromlen);
	else
		sendto(iface->fd, "", 0, 0, (struct sockaddr *) from, fromlen);
}