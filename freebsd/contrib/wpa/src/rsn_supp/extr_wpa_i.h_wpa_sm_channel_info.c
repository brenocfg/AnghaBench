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
struct wpa_channel_info {int dummy; } ;
struct TYPE_2__ {int (* channel_info ) (int /*<<< orphan*/ ,struct wpa_channel_info*) ;int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,struct wpa_channel_info*) ; 

__attribute__((used)) static inline int wpa_sm_channel_info(struct wpa_sm *sm,
				      struct wpa_channel_info *ci)
{
	if (!sm->ctx->channel_info)
		return -1;
	return sm->ctx->channel_info(sm->ctx->ctx, ci);
}