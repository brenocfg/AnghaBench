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
struct TYPE_3__ {int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ uv_buf_t ;
struct sockaddr {scalar_t__ sa_family; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  EXPECTED ; 
 scalar_t__ UV_ECANCELED ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  recv_cb_called ; 

__attribute__((used)) static void recv_cb(uv_udp_t* handle,
                    ssize_t nread,
                    const uv_buf_t* buf,
                    const struct sockaddr* addr,
                    unsigned flags) {
  if (nread == 0)
    return;

  if (nread < 0) {
    ASSERT(nread == UV_ECANCELED);
    return;
  }

  ASSERT(addr->sa_family == AF_INET);
  ASSERT(!memcmp(buf->base, EXPECTED, nread));

  recv_cb_called++;
}