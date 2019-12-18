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
struct TYPE_2__ {int (* send_mlme ) (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t,int,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t,int,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int wpa_drv_send_mlme(struct wpa_supplicant *wpa_s,
				    const u8 *data, size_t data_len, int noack,
				    unsigned int freq)
{
	if (wpa_s->driver->send_mlme)
		return wpa_s->driver->send_mlme(wpa_s->drv_priv,
						data, data_len, noack,
						freq, NULL, 0);
	return -1;
}