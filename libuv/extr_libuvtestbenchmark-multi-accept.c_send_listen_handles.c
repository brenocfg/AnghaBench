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
typedef  int /*<<< orphan*/  uv_tcp_t ;
typedef  int /*<<< orphan*/  uv_stream_t ;
typedef  int /*<<< orphan*/  uv_loop_t ;
typedef  scalar_t__ uv_handle_type ;
typedef  int /*<<< orphan*/  uv_handle_t ;
struct sockaddr {int dummy; } ;
struct server_ctx {int /*<<< orphan*/  semaphore; } ;
struct ipc_server_ctx {unsigned int num_connects; int /*<<< orphan*/  server_handle; int /*<<< orphan*/  ipc_pipe; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  IPC_PIPE_NAME ; 
 int /*<<< orphan*/  UV_RUN_DEFAULT ; 
 scalar_t__ UV_TCP ; 
 int /*<<< orphan*/  ipc_connection_cb ; 
 int /*<<< orphan*/  listen_addr ; 
 int /*<<< orphan*/  uv_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * uv_default_loop () ; 
 scalar_t__ uv_listen (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ uv_pipe_bind (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ uv_pipe_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ uv_run (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_sem_post (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_sem_wait (int /*<<< orphan*/ *) ; 
 scalar_t__ uv_tcp_bind (int /*<<< orphan*/ *,struct sockaddr const*,int /*<<< orphan*/ ) ; 
 scalar_t__ uv_tcp_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void send_listen_handles(uv_handle_type type,
                                unsigned int num_servers,
                                struct server_ctx* servers) {
  struct ipc_server_ctx ctx;
  uv_loop_t* loop;
  unsigned int i;

  loop = uv_default_loop();
  ctx.num_connects = num_servers;

  if (type == UV_TCP) {
    ASSERT(0 == uv_tcp_init(loop, (uv_tcp_t*) &ctx.server_handle));
    ASSERT(0 == uv_tcp_bind((uv_tcp_t*) &ctx.server_handle,
                            (const struct sockaddr*) &listen_addr,
                            0));
  }
  else
    ASSERT(0);

  ASSERT(0 == uv_pipe_init(loop, &ctx.ipc_pipe, 1));
  ASSERT(0 == uv_pipe_bind(&ctx.ipc_pipe, IPC_PIPE_NAME));
  ASSERT(0 == uv_listen((uv_stream_t*) &ctx.ipc_pipe, 128, ipc_connection_cb));

  for (i = 0; i < num_servers; i++)
    uv_sem_post(&servers[i].semaphore);

  ASSERT(0 == uv_run(loop, UV_RUN_DEFAULT));
  uv_close((uv_handle_t*) &ctx.server_handle, NULL);
  ASSERT(0 == uv_run(loop, UV_RUN_DEFAULT));

  for (i = 0; i < num_servers; i++)
    uv_sem_wait(&servers[i].semaphore);
}