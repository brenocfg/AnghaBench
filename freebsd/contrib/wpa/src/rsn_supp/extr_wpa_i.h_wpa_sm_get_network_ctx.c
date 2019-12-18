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
struct TYPE_2__ {void* (* get_network_ctx ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  WPA_ASSERT (void* (*) (int /*<<< orphan*/ )) ; 
 void* stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void * wpa_sm_get_network_ctx(struct wpa_sm *sm)
{
	WPA_ASSERT(sm->ctx->get_network_ctx);
	return sm->ctx->get_network_ctx(sm->ctx->ctx);
}