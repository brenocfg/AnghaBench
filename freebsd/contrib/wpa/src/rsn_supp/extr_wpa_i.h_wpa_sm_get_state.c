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
struct wpa_sm {TYPE_1__* ctx; } ;
typedef  enum wpa_states { ____Placeholder_wpa_states } wpa_states ;
struct TYPE_2__ {int (* get_state ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  WPA_ASSERT (int (*) (int /*<<< orphan*/ )) ; 
 int stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline enum wpa_states wpa_sm_get_state(struct wpa_sm *sm)
{
	WPA_ASSERT(sm->ctx->get_state);
	return sm->ctx->get_state(sm->ctx->ctx);
}