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
struct wpa_supplicant {int /*<<< orphan*/  drv_priv; TYPE_1__* driver; } ;
struct TYPE_2__ {int (* remain_on_channel ) (int /*<<< orphan*/ ,unsigned int,unsigned int) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static inline int wpa_drv_remain_on_channel(struct wpa_supplicant *wpa_s,
					    unsigned int freq,
					    unsigned int duration)
{
	if (wpa_s->driver->remain_on_channel)
		return wpa_s->driver->remain_on_channel(wpa_s->drv_priv, freq,
							duration);
	return -1;
}