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
typedef  int /*<<< orphan*/  uv_udp_t ;
typedef  int /*<<< orphan*/  uv_udp_send_t ;
typedef  int /*<<< orphan*/  uv_buf_t ;
struct sockaddr {scalar_t__ sa_family; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  on_send ; 
 scalar_t__ uv_udp_send (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,struct sockaddr const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void on_recv(uv_udp_t* handle,
                    ssize_t nread,
                    const uv_buf_t* rcvbuf,
                    const struct sockaddr* addr,
                    unsigned flags) {
  uv_udp_send_t* req;
  uv_buf_t sndbuf;

  ASSERT(nread > 0);
  ASSERT(addr->sa_family == AF_INET);

  req = malloc(sizeof(*req));
  ASSERT(req != NULL);

  sndbuf = *rcvbuf;
  ASSERT(0 == uv_udp_send(req, handle, &sndbuf, 1, addr, on_send));
}