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
typedef  int /*<<< orphan*/  uv_loop_t ;
struct signal_ctx {int signum; int one_shot; int /*<<< orphan*/  handle; int /*<<< orphan*/  stop_or_close; scalar_t__ ncalls; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  CLOSE ; 
 int /*<<< orphan*/  signal_cb ; 
 int /*<<< orphan*/  signal_cb_one_shot ; 
 scalar_t__ uv_signal_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ uv_signal_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ uv_signal_start_oneshot (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void start_watcher(uv_loop_t* loop,
                          int signum,
                          struct signal_ctx* ctx,
                          int one_shot) {
  ctx->ncalls = 0;
  ctx->signum = signum;
  ctx->stop_or_close = CLOSE;
  ctx->one_shot = one_shot;
  ASSERT(0 == uv_signal_init(loop, &ctx->handle));
  if (one_shot)
    ASSERT(0 == uv_signal_start_oneshot(&ctx->handle, signal_cb_one_shot, signum));
  else
    ASSERT(0 == uv_signal_start(&ctx->handle, signal_cb, signum));
}