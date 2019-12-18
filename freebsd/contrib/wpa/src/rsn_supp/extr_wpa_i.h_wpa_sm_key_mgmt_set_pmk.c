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
struct TYPE_2__ {int (* key_mgmt_set_pmk ) (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ;int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static inline int wpa_sm_key_mgmt_set_pmk(struct wpa_sm *sm,
					  const u8 *pmk, size_t pmk_len)
{
	if (!sm->ctx->key_mgmt_set_pmk)
		return -1;
	return sm->ctx->key_mgmt_set_pmk(sm->ctx->ctx, pmk, pmk_len);
}