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
struct TYPE_2__ {int (* send_action ) (int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t,int) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t,int) ; 

__attribute__((used)) static inline int wpa_drv_send_action(struct wpa_supplicant *wpa_s,
				      unsigned int freq,
				      unsigned int wait,
				      const u8 *dst, const u8 *src,
				      const u8 *bssid,
				      const u8 *data, size_t data_len,
				      int no_cck)
{
	if (wpa_s->driver->send_action)
		return wpa_s->driver->send_action(wpa_s->drv_priv, freq,
						  wait, dst, src, bssid,
						  data, data_len, no_cck);
	return -1;
}