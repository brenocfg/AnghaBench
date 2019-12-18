#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  cb; int /*<<< orphan*/  fd; } ;
struct TYPE_5__ {int delayed_error; unsigned long flags; TYPE_3__ io_watcher; int /*<<< orphan*/  loop; int /*<<< orphan*/  connection_cb; } ;
typedef  TYPE_1__ uv_tcp_t ;
typedef  int /*<<< orphan*/  uv_connection_cb ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  POLLIN ; 
 unsigned long UV_HANDLE_BOUND ; 
 unsigned long UV_HANDLE_TCP_SINGLE_ACCEPT ; 
 int UV__ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ atoi (char const*) ; 
 int /*<<< orphan*/  errno ; 
 char* getenv (char*) ; 
 scalar_t__ listen (int /*<<< orphan*/ ,int) ; 
 int maybe_new_socket (TYPE_1__*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  uv__io_start (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv__server_io ; 

int uv_tcp_listen(uv_tcp_t* tcp, int backlog, uv_connection_cb cb) {
  static int single_accept = -1;
  unsigned long flags;
  int err;

  if (tcp->delayed_error)
    return tcp->delayed_error;

  if (single_accept == -1) {
    const char* val = getenv("UV_TCP_SINGLE_ACCEPT");
    single_accept = (val != NULL && atoi(val) != 0);  /* Off by default. */
  }

  if (single_accept)
    tcp->flags |= UV_HANDLE_TCP_SINGLE_ACCEPT;

  flags = 0;
#if defined(__MVS__)
  /* on zOS the listen call does not bind automatically
     if the socket is unbound. Hence the manual binding to
     an arbitrary port is required to be done manually
  */
  flags |= UV_HANDLE_BOUND;
#endif
  err = maybe_new_socket(tcp, AF_INET, flags);
  if (err)
    return err;

  if (listen(tcp->io_watcher.fd, backlog))
    return UV__ERR(errno);

  tcp->connection_cb = cb;
  tcp->flags |= UV_HANDLE_BOUND;

  /* Start listening for connections. */
  tcp->io_watcher.cb = uv__server_io;
  uv__io_start(tcp->loop, &tcp->io_watcher, POLLIN);

  return 0;
}