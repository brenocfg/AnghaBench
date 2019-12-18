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
typedef  int /*<<< orphan*/  u8 ;
struct wpa_supplicant {int /*<<< orphan*/  drv_priv; TYPE_1__* driver; } ;
typedef  enum tdls_oper { ____Placeholder_tdls_oper } tdls_oper ;
struct TYPE_2__ {int (* tdls_oper ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static inline int wpa_drv_tdls_oper(struct wpa_supplicant *wpa_s,
				    enum tdls_oper oper, const u8 *peer)
{
	if (!wpa_s->driver->tdls_oper)
		return -1;
	return wpa_s->driver->tdls_oper(wpa_s->drv_priv, oper, peer);
}