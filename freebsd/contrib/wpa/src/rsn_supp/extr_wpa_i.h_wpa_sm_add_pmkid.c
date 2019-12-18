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
struct wpa_sm {TYPE_1__* ctx; } ;
struct TYPE_2__ {int (* add_pmkid ) (int /*<<< orphan*/ ,void*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ;int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  WPA_ASSERT (int (*) (int /*<<< orphan*/ ,void*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t)) ; 
 int stub1 (int /*<<< orphan*/ ,void*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static inline int wpa_sm_add_pmkid(struct wpa_sm *sm, void *network_ctx,
				   const u8 *bssid, const u8 *pmkid,
				   const u8 *cache_id, const u8 *pmk,
				   size_t pmk_len)
{
	WPA_ASSERT(sm->ctx->add_pmkid);
	return sm->ctx->add_pmkid(sm->ctx->ctx, network_ctx, bssid, pmkid,
				  cache_id, pmk, pmk_len);
}