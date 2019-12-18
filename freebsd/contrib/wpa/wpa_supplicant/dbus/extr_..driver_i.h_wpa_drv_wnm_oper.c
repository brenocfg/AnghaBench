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
typedef  int /*<<< orphan*/  u16 ;
struct wpa_supplicant {int /*<<< orphan*/  drv_priv; TYPE_1__* driver; } ;
typedef  enum wnm_oper { ____Placeholder_wnm_oper } wnm_oper ;
struct TYPE_2__ {int (* wnm_oper ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int wpa_drv_wnm_oper(struct wpa_supplicant *wpa_s,
				   enum wnm_oper oper, const u8 *peer,
				   u8 *buf, u16 *buf_len)
{
	if (!wpa_s->driver->wnm_oper)
		return -1;
	return wpa_s->driver->wnm_oper(wpa_s->drv_priv, oper, peer, buf,
				       buf_len);
}