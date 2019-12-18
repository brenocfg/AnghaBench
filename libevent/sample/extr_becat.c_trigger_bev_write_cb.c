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
struct context {int /*<<< orphan*/  out; } ;
struct bufferevent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_WRITE ; 
 int /*<<< orphan*/  bufferevent_trigger (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void trigger_bev_write_cb(struct bufferevent *bev, void *arg)
{
	struct context *ctx = arg;
	if (!ctx->out)
		return;
	bufferevent_trigger(ctx->out, EV_WRITE, 0);
}