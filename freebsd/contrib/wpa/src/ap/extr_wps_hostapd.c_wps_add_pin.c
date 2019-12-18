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
struct wps_add_pin_data {int /*<<< orphan*/  added; int /*<<< orphan*/  timeout; int /*<<< orphan*/  pin_len; int /*<<< orphan*/  pin; int /*<<< orphan*/  uuid; int /*<<< orphan*/  addr; } ;
struct hostapd_data {TYPE_1__* wps; } ;
struct TYPE_2__ {int /*<<< orphan*/  registrar; } ;

/* Variables and functions */
 int wps_registrar_add_pin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wps_add_pin(struct hostapd_data *hapd, void *ctx)
{
	struct wps_add_pin_data *data = ctx;
	int ret;

	if (hapd->wps == NULL)
		return 0;
	ret = wps_registrar_add_pin(hapd->wps->registrar, data->addr,
				    data->uuid, data->pin, data->pin_len,
				    data->timeout);
	if (ret == 0)
		data->added++;
	return ret;
}