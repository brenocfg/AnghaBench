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
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  sockname ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  check_sockname (struct sockaddr*,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getsocknamecount ; 
 int /*<<< orphan*/  memset (struct sockaddr*,int,int) ; 
 int /*<<< orphan*/  udp ; 
 int /*<<< orphan*/  uv_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int uv_udp_getsockname (int /*<<< orphan*/ *,struct sockaddr*,int*) ; 

__attribute__((used)) static void udp_recv(uv_udp_t* handle,
                     ssize_t nread,
                     const uv_buf_t* buf,
                     const struct sockaddr* addr,
                     unsigned flags) {
  struct sockaddr sockname;
  int namelen;
  int r;

  ASSERT(nread >= 0);
  free(buf->base);

  if (nread == 0) {
    return;
  }

  memset(&sockname, -1, sizeof sockname);
  namelen = sizeof(sockname);
  r = uv_udp_getsockname(&udp, &sockname, &namelen);
  ASSERT(r == 0);
  check_sockname(&sockname, "0.0.0.0", 0, "udp receiving socket");
  getsocknamecount++;

  uv_close((uv_handle_t*) &udp, NULL);
  uv_close((uv_handle_t*) handle, NULL);
}