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
struct wpa_auth_iface_iter_data {int (* cb ) (struct wpa_authenticator*,void*) ;void* cb_ctx; } ;
struct hostapd_data {TYPE_1__* iface; } ;
struct TYPE_4__ {int (* for_each_interface ) (TYPE_2__*,int /*<<< orphan*/ ,struct wpa_auth_iface_iter_data*) ;} ;
struct TYPE_3__ {TYPE_2__* interfaces; } ;

/* Variables and functions */
 int stub1 (TYPE_2__*,int /*<<< orphan*/ ,struct wpa_auth_iface_iter_data*) ; 
 int /*<<< orphan*/  wpa_auth_iface_iter ; 

__attribute__((used)) static int hostapd_wpa_auth_for_each_auth(
	void *ctx, int (*cb)(struct wpa_authenticator *sm, void *ctx),
	void *cb_ctx)
{
	struct hostapd_data *hapd = ctx;
	struct wpa_auth_iface_iter_data data;
	if (hapd->iface->interfaces == NULL ||
	    hapd->iface->interfaces->for_each_interface == NULL)
		return -1;
	data.cb = cb;
	data.cb_ctx = cb_ctx;
	return hapd->iface->interfaces->for_each_interface(
		hapd->iface->interfaces, wpa_auth_iface_iter, &data);
}