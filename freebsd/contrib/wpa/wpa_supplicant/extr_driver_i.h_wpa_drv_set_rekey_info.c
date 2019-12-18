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
struct TYPE_2__ {int /*<<< orphan*/  (* set_rekey_info ) (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static inline void wpa_drv_set_rekey_info(struct wpa_supplicant *wpa_s,
					  const u8 *kek, size_t kek_len,
					  const u8 *kck, size_t kck_len,
					  const u8 *replay_ctr)
{
	if (!wpa_s->driver->set_rekey_info)
		return;
	wpa_s->driver->set_rekey_info(wpa_s->drv_priv, kek, kek_len,
				      kck, kck_len, replay_ctr);
}