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
typedef  int /*<<< orphan*/  uv_stream_t ;
typedef  int /*<<< orphan*/  uv_loop_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;
struct server_ctx {int /*<<< orphan*/  server_handle; int /*<<< orphan*/  semaphore; int /*<<< orphan*/  async_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  UV_RUN_DEFAULT ; 
 int /*<<< orphan*/  get_listen_handle (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sv_async_cb ; 
 int /*<<< orphan*/  sv_connection_cb ; 
 scalar_t__ uv_async_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ uv_listen (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_loop_close (int /*<<< orphan*/ *) ; 
 scalar_t__ uv_loop_init (int /*<<< orphan*/ *) ; 
 scalar_t__ uv_run (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_sem_post (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_sem_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_unref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void server_cb(void *arg) {
  struct server_ctx *ctx;
  uv_loop_t loop;

  ctx = arg;
  ASSERT(0 == uv_loop_init(&loop));

  ASSERT(0 == uv_async_init(&loop, &ctx->async_handle, sv_async_cb));
  uv_unref((uv_handle_t*) &ctx->async_handle);

  /* Wait until the main thread is ready. */
  uv_sem_wait(&ctx->semaphore);
  get_listen_handle(&loop, (uv_stream_t*) &ctx->server_handle);
  uv_sem_post(&ctx->semaphore);

  /* Now start the actual benchmark. */
  ASSERT(0 == uv_listen((uv_stream_t*) &ctx->server_handle,
                        128,
                        sv_connection_cb));
  ASSERT(0 == uv_run(&loop, UV_RUN_DEFAULT));

  uv_loop_close(&loop);
}