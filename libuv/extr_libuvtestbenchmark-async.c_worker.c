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
struct ctx {int /*<<< orphan*/  loop; int /*<<< orphan*/  main_async; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  UV_RUN_DEFAULT ; 
 scalar_t__ uv_async_send (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_loop_close (int /*<<< orphan*/ *) ; 
 scalar_t__ uv_run (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void worker(void* arg) {
  struct ctx* ctx = arg;
  ASSERT(0 == uv_async_send(&ctx->main_async));
  ASSERT(0 == uv_run(&ctx->loop, UV_RUN_DEFAULT));
  uv_loop_close(&ctx->loop);
}