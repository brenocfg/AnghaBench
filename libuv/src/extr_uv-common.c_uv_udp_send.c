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
typedef  int /*<<< orphan*/  uv_udp_send_cb ;
typedef  int /*<<< orphan*/  uv_buf_t ;
struct sockaddr {int dummy; } ;

/* Variables and functions */
 int uv__udp_check_before_send (int /*<<< orphan*/ *,struct sockaddr const*) ; 
 int uv__udp_send (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int,struct sockaddr const*,int,int /*<<< orphan*/ ) ; 

int uv_udp_send(uv_udp_send_t* req,
                uv_udp_t* handle,
                const uv_buf_t bufs[],
                unsigned int nbufs,
                const struct sockaddr* addr,
                uv_udp_send_cb send_cb) {
  int addrlen;

  addrlen = uv__udp_check_before_send(handle, addr);
  if (addrlen < 0)
    return addrlen;

  return uv__udp_send(req, handle, bufs, nbufs, addr, addrlen, send_cb);
}