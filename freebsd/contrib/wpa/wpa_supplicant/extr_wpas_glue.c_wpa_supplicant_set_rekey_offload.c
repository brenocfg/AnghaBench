#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wpa_supplicant {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  wpa_drv_set_rekey_info (struct wpa_supplicant*,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void wpa_supplicant_set_rekey_offload(void *ctx,
					     const u8 *kek, size_t kek_len,
					     const u8 *kck, size_t kck_len,
					     const u8 *replay_ctr)
{
	struct wpa_supplicant *wpa_s = ctx;

	wpa_drv_set_rekey_info(wpa_s, kek, kek_len, kck, kck_len, replay_ctr);
}