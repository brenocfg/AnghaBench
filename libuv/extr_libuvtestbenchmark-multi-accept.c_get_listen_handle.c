#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* data; } ;
typedef  TYPE_1__ uv_stream_t ;
typedef  int /*<<< orphan*/  uv_loop_t ;
struct ipc_client_ctx {int /*<<< orphan*/  ipc_pipe; int /*<<< orphan*/  connect_req; TYPE_1__* server_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  IPC_PIPE_NAME ; 
 int /*<<< orphan*/  UV_RUN_DEFAULT ; 
 int /*<<< orphan*/  ipc_connect_cb ; 
 int /*<<< orphan*/  uv_pipe_connect (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ uv_pipe_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ uv_run (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void get_listen_handle(uv_loop_t* loop, uv_stream_t* server_handle) {
  struct ipc_client_ctx ctx;

  ctx.server_handle = server_handle;
  ctx.server_handle->data = "server handle";

  ASSERT(0 == uv_pipe_init(loop, &ctx.ipc_pipe, 1));
  uv_pipe_connect(&ctx.connect_req,
                  &ctx.ipc_pipe,
                  IPC_PIPE_NAME,
                  ipc_connect_cb);
  ASSERT(0 == uv_run(loop, UV_RUN_DEFAULT));
}