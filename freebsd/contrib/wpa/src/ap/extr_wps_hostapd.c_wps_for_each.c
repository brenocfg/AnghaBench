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
struct wps_for_each_data {int (* func ) (struct hostapd_data*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  ctx; struct hostapd_data* calling_hapd; } ;
struct hostapd_iface {size_t num_bss; struct hostapd_data** bss; } ;
struct hostapd_data {TYPE_1__* conf; } ;
struct TYPE_2__ {scalar_t__ wps_independent; } ;

/* Variables and functions */
 int stub1 (struct hostapd_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wps_for_each(struct hostapd_iface *iface, void *ctx)
{
	struct wps_for_each_data *data = ctx;
	size_t j;

	if (iface == NULL)
		return 0;
	for (j = 0; j < iface->num_bss; j++) {
		struct hostapd_data *hapd = iface->bss[j];
		int ret;

		if (hapd != data->calling_hapd &&
		    (hapd->conf->wps_independent ||
		     data->calling_hapd->conf->wps_independent))
			continue;

		ret = data->func(hapd, data->ctx);
		if (ret)
			return ret;
	}

	return 0;
}