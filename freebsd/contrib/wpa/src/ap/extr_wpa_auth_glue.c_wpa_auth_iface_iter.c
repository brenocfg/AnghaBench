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
struct wpa_auth_iface_iter_data {int /*<<< orphan*/  cb_ctx; scalar_t__ (* cb ) (scalar_t__,int /*<<< orphan*/ ) ;} ;
struct hostapd_iface {size_t num_bss; TYPE_1__** bss; } ;
struct TYPE_2__ {scalar_t__ wpa_auth; } ;

/* Variables and functions */
 scalar_t__ stub1 (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wpa_auth_iface_iter(struct hostapd_iface *iface, void *ctx)
{
	struct wpa_auth_iface_iter_data *data = ctx;
	size_t i;
	for (i = 0; i < iface->num_bss; i++) {
		if (iface->bss[i]->wpa_auth &&
		    data->cb(iface->bss[i]->wpa_auth, data->cb_ctx))
			return 1;
	}
	return 0;
}