#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  fd; } ;
struct TYPE_6__ {int /*<<< orphan*/  flags; TYPE_1__ io_watcher; } ;
typedef  TYPE_2__ uv_udp_t ;
struct sockaddr {int /*<<< orphan*/  sa_family; } ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  UV_HANDLE_UDP_CONNECTED ; 
 int UV__ERR (scalar_t__) ; 
 int connect (int /*<<< orphan*/ ,struct sockaddr const*,unsigned int) ; 
 scalar_t__ errno ; 
 int uv__udp_maybe_deferred_bind (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int uv__udp_connect(uv_udp_t* handle,
                    const struct sockaddr* addr,
                    unsigned int addrlen) {
  int err;

  err = uv__udp_maybe_deferred_bind(handle, addr->sa_family, 0);
  if (err)
    return err;

  do {
    errno = 0;
    err = connect(handle->io_watcher.fd, addr, addrlen);
  } while (err == -1 && errno == EINTR);

  if (err)
    return UV__ERR(errno);

  handle->flags |= UV_HANDLE_UDP_CONNECTED;

  return 0;
}