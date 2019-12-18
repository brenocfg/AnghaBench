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
struct wpa_sm {int /*<<< orphan*/  key_mgmt; int /*<<< orphan*/  network_ctx; int /*<<< orphan*/  own_addr; int /*<<< orphan*/  pmksa; int /*<<< orphan*/  cur_pmksa; } ;

/* Variables and functions */
 int /*<<< orphan*/  pmksa_cache_add (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

void wpa_sm_pmksa_cache_add(struct wpa_sm *sm, const u8 *pmk, size_t pmk_len,
			    const u8 *pmkid, const u8 *bssid,
			    const u8 *fils_cache_id)
{
	sm->cur_pmksa = pmksa_cache_add(sm->pmksa, pmk, pmk_len, pmkid, NULL, 0,
					bssid, sm->own_addr, sm->network_ctx,
					sm->key_mgmt, fils_cache_id);
}