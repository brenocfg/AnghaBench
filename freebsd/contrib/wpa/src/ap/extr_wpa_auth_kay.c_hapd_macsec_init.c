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
struct macsec_init_params {int dummy; } ;
struct hostapd_data {int /*<<< orphan*/  drv_priv; TYPE_1__* driver; } ;
struct TYPE_2__ {int (* macsec_init ) (int /*<<< orphan*/ ,struct macsec_init_params*) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,struct macsec_init_params*) ; 

__attribute__((used)) static int hapd_macsec_init(void *priv, struct macsec_init_params *params)
{
	struct hostapd_data *hapd = priv;

	if (!hapd->driver->macsec_init)
		return -1;
	return hapd->driver->macsec_init(hapd->drv_priv, params);
}