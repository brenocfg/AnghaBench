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
struct wpa_sm {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int pmksa_cache_set_current(struct wpa_sm *sm, const u8 *pmkid,
					  const u8 *bssid,
					  void *network_ctx,
					  int try_opportunistic,
					  const u8 *fils_cache_id,
					  int akmp)
{
	return -1;
}