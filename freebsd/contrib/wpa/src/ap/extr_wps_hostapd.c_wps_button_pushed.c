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
struct wps_button_pushed_ctx {int /*<<< orphan*/  p2p_dev_addr; int /*<<< orphan*/  count; } ;
struct hostapd_data {TYPE_1__* wps; } ;
struct TYPE_2__ {int /*<<< orphan*/  registrar; } ;

/* Variables and functions */
 int wps_registrar_button_pushed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wps_button_pushed(struct hostapd_data *hapd, void *ctx)
{
	struct wps_button_pushed_ctx *data = ctx;

	if (hapd->wps) {
		data->count++;
		return wps_registrar_button_pushed(hapd->wps->registrar,
						   data->p2p_dev_addr);
	}

	return 0;
}