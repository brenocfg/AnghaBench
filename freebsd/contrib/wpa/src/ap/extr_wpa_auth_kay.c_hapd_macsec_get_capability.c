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
struct hostapd_data {int /*<<< orphan*/  drv_priv; TYPE_1__* driver; } ;
typedef  enum macsec_cap { ____Placeholder_macsec_cap } macsec_cap ;
struct TYPE_2__ {int (* macsec_get_capability ) (int /*<<< orphan*/ ,int*) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int hapd_macsec_get_capability(void *priv, enum macsec_cap *cap)
{
	struct hostapd_data *hapd = priv;

	if (!hapd->driver->macsec_get_capability)
		return -1;
	return hapd->driver->macsec_get_capability(hapd->drv_priv, cap);
}