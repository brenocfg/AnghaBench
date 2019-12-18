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
struct transmit_sa {int dummy; } ;
struct hostapd_data {int /*<<< orphan*/  drv_priv; TYPE_1__* driver; } ;
struct TYPE_2__ {int (* create_transmit_sa ) (int /*<<< orphan*/ ,struct transmit_sa*) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,struct transmit_sa*) ; 

__attribute__((used)) static int hapd_create_transmit_sa(void *priv, struct transmit_sa *sa)
{
	struct hostapd_data *hapd = priv;

	if (!hapd->driver->create_transmit_sa)
		return -1;
	return hapd->driver->create_transmit_sa(hapd->drv_priv, sa);
}