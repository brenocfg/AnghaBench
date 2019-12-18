#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  kck_len; int /*<<< orphan*/  kck; int /*<<< orphan*/  kek_len; int /*<<< orphan*/  kek; } ;
struct wpa_sm {int /*<<< orphan*/  rx_replay_counter; TYPE_2__ ptk; TYPE_1__* ctx; } ;
struct TYPE_3__ {int /*<<< orphan*/  ctx; int /*<<< orphan*/  (* set_rekey_offload ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void wpa_sm_set_rekey_offload(struct wpa_sm *sm)
{
	if (!sm->ctx->set_rekey_offload)
		return;
	sm->ctx->set_rekey_offload(sm->ctx->ctx, sm->ptk.kek, sm->ptk.kek_len,
				   sm->ptk.kck, sm->ptk.kck_len,
				   sm->rx_replay_counter);
}