#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uv_udp_t ;
typedef  int /*<<< orphan*/  uv_udp_send_t ;
struct TYPE_5__ {int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ uv_buf_t ;
struct sockaddr {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  CHECK_HANDLE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  memcmp (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sv_recv_cb_called ; 
 int /*<<< orphan*/  sv_send_cb ; 
 TYPE_1__ uv_buf_init (char*,int) ; 
 int uv_udp_recv_stop (int /*<<< orphan*/ *) ; 
 int uv_udp_send (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int,struct sockaddr const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sv_recv_cb(uv_udp_t* handle,
                       ssize_t nread,
                       const uv_buf_t* rcvbuf,
                       const struct sockaddr* addr,
                       unsigned flags) {
  uv_udp_send_t* req;
  uv_buf_t sndbuf;
  int r;

  if (nread < 0) {
    ASSERT(0 && "unexpected error");
  }

  if (nread == 0) {
    /* Returning unused buffer. Don't count towards sv_recv_cb_called */
    ASSERT(addr == NULL);
    return;
  }

  CHECK_HANDLE(handle);
  ASSERT(flags == 0);

  ASSERT(addr != NULL);
  ASSERT(nread == 4);
  ASSERT(!memcmp("PING", rcvbuf->base, nread));

  /* FIXME? `uv_udp_recv_stop` does what it says: recv_cb is not called
    * anymore. That's problematic because the read buffer won't be returned
    * either... Not sure I like that but it's consistent with `uv_read_stop`.
    */
  r = uv_udp_recv_stop(handle);
  ASSERT(r == 0);

  req = malloc(sizeof *req);
  ASSERT(req != NULL);

  sndbuf = uv_buf_init("PONG", 4);
  r = uv_udp_send(req, handle, &sndbuf, 1, addr, sv_send_cb);
  ASSERT(r == 0);

  sv_recv_cb_called++;
}