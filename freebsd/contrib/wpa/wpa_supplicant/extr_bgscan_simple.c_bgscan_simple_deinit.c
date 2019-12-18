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
struct bgscan_simple_data {int /*<<< orphan*/  wpa_s; scalar_t__ signal_threshold; } ;

/* Variables and functions */
 int /*<<< orphan*/  bgscan_simple_timeout ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct bgscan_simple_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (struct bgscan_simple_data*) ; 
 int /*<<< orphan*/  wpa_drv_signal_monitor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bgscan_simple_deinit(void *priv)
{
	struct bgscan_simple_data *data = priv;
	eloop_cancel_timeout(bgscan_simple_timeout, data, NULL);
	if (data->signal_threshold)
		wpa_drv_signal_monitor(data->wpa_s, 0, 0);
	os_free(data);
}