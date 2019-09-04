#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* data; } ;
typedef  TYPE_1__ uv_tcp_t ;
typedef  int /*<<< orphan*/  uv_loop_t ;
typedef  int uint64_t ;
struct sockaddr {int dummy; } ;
struct server_ctx {unsigned int num_connects; int /*<<< orphan*/  semaphore; int /*<<< orphan*/  thread_id; int /*<<< orphan*/  async_handle; int /*<<< orphan*/  idle_handle; int /*<<< orphan*/  connect_req; int /*<<< orphan*/  client_handle; } ;
struct client_ctx {unsigned int num_connects; int /*<<< orphan*/  semaphore; int /*<<< orphan*/  thread_id; int /*<<< orphan*/  async_handle; int /*<<< orphan*/  idle_handle; int /*<<< orphan*/  connect_req; int /*<<< orphan*/  client_handle; } ;
typedef  int /*<<< orphan*/  servers ;
typedef  int /*<<< orphan*/  clients ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  MAKE_VALGRIND_HAPPY () ; 
 unsigned int NUM_CONNECTS ; 
 int /*<<< orphan*/  TEST_PORT ; 
 int /*<<< orphan*/  UV_RUN_DEFAULT ; 
 int /*<<< orphan*/  UV_TCP ; 
 struct server_ctx* calloc (unsigned int,int) ; 
 int /*<<< orphan*/  cl_connect_cb ; 
 int /*<<< orphan*/  free (struct server_ctx*) ; 
 int /*<<< orphan*/  listen_addr ; 
 int /*<<< orphan*/  printf (char*,unsigned int,double,double,...) ; 
 int /*<<< orphan*/  send_listen_handles (int /*<<< orphan*/ ,unsigned int,struct server_ctx*) ; 
 int /*<<< orphan*/  server_cb ; 
 int /*<<< orphan*/  uv_async_send (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * uv_default_loop () ; 
 int uv_hrtime () ; 
 scalar_t__ uv_idle_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ uv_ip4_addr (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ uv_run (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_sem_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ uv_sem_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ uv_tcp_connect (int /*<<< orphan*/ *,TYPE_1__*,struct sockaddr const*,int /*<<< orphan*/ ) ; 
 scalar_t__ uv_tcp_init (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ uv_thread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct server_ctx*) ; 
 scalar_t__ uv_thread_join (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int test_tcp(unsigned int num_servers, unsigned int num_clients) {
  struct server_ctx* servers;
  struct client_ctx* clients;
  uv_loop_t* loop;
  uv_tcp_t* handle;
  unsigned int i;
  double time;

  ASSERT(0 == uv_ip4_addr("127.0.0.1", TEST_PORT, &listen_addr));
  loop = uv_default_loop();

  servers = calloc(num_servers, sizeof(servers[0]));
  clients = calloc(num_clients, sizeof(clients[0]));
  ASSERT(servers != NULL);
  ASSERT(clients != NULL);

  /* We're making the assumption here that from the perspective of the
   * OS scheduler, threads are functionally equivalent to and interchangeable
   * with full-blown processes.
   */
  for (i = 0; i < num_servers; i++) {
    struct server_ctx* ctx = servers + i;
    ASSERT(0 == uv_sem_init(&ctx->semaphore, 0));
    ASSERT(0 == uv_thread_create(&ctx->thread_id, server_cb, ctx));
  }

  send_listen_handles(UV_TCP, num_servers, servers);

  for (i = 0; i < num_clients; i++) {
    struct client_ctx* ctx = clients + i;
    ctx->num_connects = NUM_CONNECTS / num_clients;
    handle = (uv_tcp_t*) &ctx->client_handle;
    handle->data = "client handle";
    ASSERT(0 == uv_tcp_init(loop, handle));
    ASSERT(0 == uv_tcp_connect(&ctx->connect_req,
                               handle,
                               (const struct sockaddr*) &listen_addr,
                               cl_connect_cb));
    ASSERT(0 == uv_idle_init(loop, &ctx->idle_handle));
  }

  {
    uint64_t t = uv_hrtime();
    ASSERT(0 == uv_run(loop, UV_RUN_DEFAULT));
    t = uv_hrtime() - t;
    time = t / 1e9;
  }

  for (i = 0; i < num_servers; i++) {
    struct server_ctx* ctx = servers + i;
    uv_async_send(&ctx->async_handle);
    ASSERT(0 == uv_thread_join(&ctx->thread_id));
    uv_sem_destroy(&ctx->semaphore);
  }

  printf("accept%u: %.0f accepts/sec (%u total)\n",
         num_servers,
         NUM_CONNECTS / time,
         NUM_CONNECTS);

  for (i = 0; i < num_servers; i++) {
    struct server_ctx* ctx = servers + i;
    printf("  thread #%u: %.0f accepts/sec (%u total, %.1f%%)\n",
           i,
           ctx->num_connects / time,
           ctx->num_connects,
           ctx->num_connects * 100.0 / NUM_CONNECTS);
  }

  free(clients);
  free(servers);

  MAKE_VALGRIND_HAPPY();
  return 0;
}