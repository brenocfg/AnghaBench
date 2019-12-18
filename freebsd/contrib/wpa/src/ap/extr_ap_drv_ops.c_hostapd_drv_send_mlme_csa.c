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
typedef  int /*<<< orphan*/  u16 ;
struct hostapd_data {int /*<<< orphan*/  drv_priv; TYPE_1__* driver; } ;
struct TYPE_2__ {int (* send_mlme ) (int /*<<< orphan*/ ,void const*,size_t,int,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,void const*,size_t,int,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 

int hostapd_drv_send_mlme_csa(struct hostapd_data *hapd,
			      const void *msg, size_t len, int noack,
			      const u16 *csa_offs, size_t csa_offs_len)
{
	if (hapd->driver == NULL || hapd->driver->send_mlme == NULL)
		return 0;
	return hapd->driver->send_mlme(hapd->drv_priv, msg, len, noack, 0,
				       csa_offs, csa_offs_len);
}