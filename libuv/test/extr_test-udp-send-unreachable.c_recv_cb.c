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
typedef  int /*<<< orphan*/  uv_buf_t ;
struct sockaddr {int dummy; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  CHECK_HANDLE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  recv_cb_called ; 

__attribute__((used)) static void recv_cb(uv_udp_t* handle,
                       ssize_t nread,
                       const uv_buf_t* rcvbuf,
                       const struct sockaddr* addr,
                       unsigned flags) {
  CHECK_HANDLE(handle);
  recv_cb_called++;

  if (nread < 0) {
    ASSERT(0 && "unexpected error");
  } else if (nread == 0) {
    /* Returning unused buffer */
    ASSERT(addr == NULL);
  } else {
    ASSERT(addr != NULL);
  }
}