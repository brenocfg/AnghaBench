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
struct wpa_supplicant {int /*<<< orphan*/  extended_capa_len; int /*<<< orphan*/  extended_capa_mask; int /*<<< orphan*/  extended_capa; int /*<<< orphan*/  drv_priv; TYPE_1__* driver; } ;
typedef  enum wpa_driver_if_type { ____Placeholder_wpa_driver_if_type } wpa_driver_if_type ;
struct TYPE_2__ {int (* get_ext_capab ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int wpa_drv_get_ext_capa(struct wpa_supplicant *wpa_s,
				       enum wpa_driver_if_type type)
{
	if (!wpa_s->driver->get_ext_capab)
		return -1;
	return wpa_s->driver->get_ext_capab(wpa_s->drv_priv, type,
					    &wpa_s->extended_capa,
					    &wpa_s->extended_capa_mask,
					    &wpa_s->extended_capa_len);
}