#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  fd; } ;
struct TYPE_5__ {int /*<<< orphan*/  flags; TYPE_1__ io_watcher; } ;
typedef  TYPE_2__ uv_udp_t ;
struct sockaddr {int /*<<< orphan*/  sa_family; } ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 scalar_t__ EAFNOSUPPORT ; 
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  UV_HANDLE_UDP_CONNECTED ; 
 int UV__ERR (scalar_t__) ; 
 int connect (int /*<<< orphan*/ ,struct sockaddr*,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  memset (struct sockaddr*,int /*<<< orphan*/ ,int) ; 

int uv__udp_disconnect(uv_udp_t* handle) {
    int r;
    struct sockaddr addr;

    memset(&addr, 0, sizeof(addr));

    addr.sa_family = AF_UNSPEC;

    do {
      errno = 0;
      r = connect(handle->io_watcher.fd, &addr, sizeof(addr));
    } while (r == -1 && errno == EINTR);

    if (r == -1 && errno != EAFNOSUPPORT)
      return UV__ERR(errno);

    handle->flags &= ~UV_HANDLE_UDP_CONNECTED;
    return 0;
}