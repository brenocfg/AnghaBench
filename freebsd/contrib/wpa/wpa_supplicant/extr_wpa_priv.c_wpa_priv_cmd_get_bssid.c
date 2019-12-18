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
typedef  char u8 ;
struct wpa_priv_interface {int /*<<< orphan*/  fd; int /*<<< orphan*/ * drv_priv; TYPE_1__* driver; } ;
struct sockaddr_un {int dummy; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;
struct TYPE_2__ {scalar_t__ (* get_bssid ) (int /*<<< orphan*/ *,char*) ;} ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  sendto (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,struct sockaddr*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void wpa_priv_cmd_get_bssid(struct wpa_priv_interface *iface,
				   struct sockaddr_un *from, socklen_t fromlen)
{
	u8 bssid[ETH_ALEN];

	if (iface->drv_priv == NULL)
		goto fail;

	if (iface->driver->get_bssid == NULL ||
	    iface->driver->get_bssid(iface->drv_priv, bssid) < 0)
		goto fail;

	sendto(iface->fd, bssid, ETH_ALEN, 0, (struct sockaddr *) from,
	       fromlen);
	return;

fail:
	sendto(iface->fd, "", 0, 0, (struct sockaddr *) from, fromlen);
}