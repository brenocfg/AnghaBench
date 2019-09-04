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
struct sockaddr {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  client ; 
 int /*<<< orphan*/  close_cb ; 
 scalar_t__ memcmp (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  server ; 
 int sv_recv_cb_called ; 
 int /*<<< orphan*/  uv_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sv_recv_cb(uv_udp_t* handle,
                       ssize_t nread,
                       const uv_buf_t* rcvbuf,
                       const struct sockaddr* addr,
                       unsigned flags) {
  if (nread > 0) {
    ASSERT(nread == 4);
    ASSERT(addr != NULL);
    ASSERT(memcmp("EXIT", rcvbuf->base, nread) == 0);
    if (++sv_recv_cb_called == 4) {
      uv_close((uv_handle_t*) &server, close_cb);
      uv_close((uv_handle_t*) &client, close_cb);
    }
  }
}