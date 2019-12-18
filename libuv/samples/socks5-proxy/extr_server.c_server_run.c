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
typedef  int /*<<< orphan*/  uv_loop_t ;
struct TYPE_3__ {int /*<<< orphan*/  bind_host; } ;
struct addrinfo {int /*<<< orphan*/ * servers; int /*<<< orphan*/  getaddrinfo_req; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; int /*<<< orphan*/ * loop; TYPE_1__ config; } ;
typedef  int /*<<< orphan*/  state ;
typedef  struct addrinfo server_state ;
typedef  TYPE_1__ server_config ;
typedef  int /*<<< orphan*/  hints ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  UV_RUN_DEFAULT ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  do_bind ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int uv_getaddrinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct addrinfo*) ; 
 int /*<<< orphan*/  uv_loop_delete (int /*<<< orphan*/ *) ; 
 scalar_t__ uv_run (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_strerror (int) ; 

int server_run(const server_config *cf, uv_loop_t *loop) {
  struct addrinfo hints;
  server_state state;
  int err;

  memset(&state, 0, sizeof(state));
  state.servers = NULL;
  state.config = *cf;
  state.loop = loop;

  /* Resolve the address of the interface that we should bind to.
   * The getaddrinfo callback starts the server and everything else.
   */
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;

  err = uv_getaddrinfo(loop,
                       &state.getaddrinfo_req,
                       do_bind,
                       cf->bind_host,
                       NULL,
                       &hints);
  if (err != 0) {
    pr_err("getaddrinfo: %s", uv_strerror(err));
    return err;
  }

  /* Start the event loop.  Control continues in do_bind(). */
  if (uv_run(loop, UV_RUN_DEFAULT)) {
    abort();
  }

  /* Please Valgrind. */
  uv_loop_delete(loop);
  free(state.servers);
  return 0;
}