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
typedef  enum wpa_alg { ____Placeholder_wpa_alg } wpa_alg ;
struct TYPE_2__ {int (* set_key ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*,int,int,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,size_t) ;int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  WPA_ASSERT (int (*) (int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*,int,int,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,size_t)) ; 
 int stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*,int,int,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static inline int wpa_sm_set_key(struct wpa_sm *sm, enum wpa_alg alg,
				 const u8 *addr, int key_idx, int set_tx,
				 const u8 *seq, size_t seq_len,
				 const u8 *key, size_t key_len)
{
	WPA_ASSERT(sm->ctx->set_key);
	return sm->ctx->set_key(sm->ctx->ctx, alg, addr, key_idx, set_tx,
				seq, seq_len, key, key_len);
}