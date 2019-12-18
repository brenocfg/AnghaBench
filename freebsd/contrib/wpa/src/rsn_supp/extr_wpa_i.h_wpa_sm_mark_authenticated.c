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
struct TYPE_2__ {int (* mark_authenticated ) (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ;int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static inline int wpa_sm_mark_authenticated(struct wpa_sm *sm,
					    const u8 *target_ap)
{
	if (sm->ctx->mark_authenticated)
		return sm->ctx->mark_authenticated(sm->ctx->ctx, target_ap);
	return -1;
}