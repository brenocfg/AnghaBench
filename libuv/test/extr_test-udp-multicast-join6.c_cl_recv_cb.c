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
typedef  int /*<<< orphan*/  uv_udp_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;
struct TYPE_3__ {int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ uv_buf_t ;
struct sockaddr_in6 {int dummy; } ;
struct sockaddr {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  source_addr ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  CHECK_HANDLE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INTERFACE_ADDR ; 
 int /*<<< orphan*/  MULTICAST_ADDR ; 
 int /*<<< orphan*/  UV_JOIN_GROUP ; 
 int /*<<< orphan*/  UV_LEAVE_GROUP ; 
 int cl_recv_cb_called ; 
 int /*<<< orphan*/  close_cb ; 
 int do_send (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcmp (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  req_ss ; 
 int /*<<< orphan*/  server ; 
 int /*<<< orphan*/  uv_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int uv_ip6_name (struct sockaddr_in6 const*,char*,int) ; 
 int uv_udp_set_membership (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int uv_udp_set_source_membership (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cl_recv_cb(uv_udp_t* handle,
                       ssize_t nread,
                       const uv_buf_t* buf,
                       const struct sockaddr* addr,
                       unsigned flags) {
  CHECK_HANDLE(handle);
  ASSERT(flags == 0);

  if (nread < 0) {
    ASSERT(0 && "unexpected error");
  }

  if (nread == 0) {
    /* Returning unused buffer. Don't count towards cl_recv_cb_called */
    ASSERT(addr == NULL);
    return;
  }

  ASSERT(addr != NULL);
  ASSERT(nread == 4);
  ASSERT(!memcmp("PING", buf->base, nread));

  cl_recv_cb_called++;

  if (cl_recv_cb_called == 2) {
    /* we are done with the server handle, we can close it */
    uv_close((uv_handle_t*) &server, close_cb);
  } else {
    int r;
    char source_addr[64];

    r = uv_ip6_name((const struct sockaddr_in6*)addr, source_addr, sizeof(source_addr));
    ASSERT(r == 0);

    r = uv_udp_set_membership(&server, MULTICAST_ADDR, INTERFACE_ADDR, UV_LEAVE_GROUP);
    ASSERT(r == 0);

    r = uv_udp_set_source_membership(&server, MULTICAST_ADDR, INTERFACE_ADDR, source_addr, UV_JOIN_GROUP);
    ASSERT(r == 0);

    r = do_send(&req_ss);
    ASSERT(r == 0);
  }
}