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
struct TYPE_4__ {int fd; } ;
struct TYPE_5__ {int /*<<< orphan*/  flags; TYPE_1__ io_watcher; } ;
typedef  TYPE_2__ uv_udp_t ;
struct sockaddr {scalar_t__ sa_family; } ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 scalar_t__ EAFNOSUPPORT ; 
 int /*<<< orphan*/  IPPROTO_IPV6 ; 
 int /*<<< orphan*/  IPV6_V6ONLY ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int UV_EINVAL ; 
 int UV_ENOTSUP ; 
 int /*<<< orphan*/  UV_HANDLE_BOUND ; 
 int /*<<< orphan*/  UV_HANDLE_IPV6 ; 
 unsigned int UV_UDP_IPV6ONLY ; 
 unsigned int UV_UDP_REUSEADDR ; 
 int UV__ERR (scalar_t__) ; 
 scalar_t__ bind (int,struct sockaddr const*,unsigned int) ; 
 scalar_t__ errno ; 
 int setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int uv__set_reuse (int) ; 
 int uv__socket (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int uv__udp_bind(uv_udp_t* handle,
                 const struct sockaddr* addr,
                 unsigned int addrlen,
                 unsigned int flags) {
  int err;
  int yes;
  int fd;

  /* Check for bad flags. */
  if (flags & ~(UV_UDP_IPV6ONLY | UV_UDP_REUSEADDR))
    return UV_EINVAL;

  /* Cannot set IPv6-only mode on non-IPv6 socket. */
  if ((flags & UV_UDP_IPV6ONLY) && addr->sa_family != AF_INET6)
    return UV_EINVAL;

  fd = handle->io_watcher.fd;
  if (fd == -1) {
    err = uv__socket(addr->sa_family, SOCK_DGRAM, 0);
    if (err < 0)
      return err;
    fd = err;
    handle->io_watcher.fd = fd;
  }

  if (flags & UV_UDP_REUSEADDR) {
    err = uv__set_reuse(fd);
    if (err)
      return err;
  }

  if (flags & UV_UDP_IPV6ONLY) {
#ifdef IPV6_V6ONLY
    yes = 1;
    if (setsockopt(fd, IPPROTO_IPV6, IPV6_V6ONLY, &yes, sizeof yes) == -1) {
      err = UV__ERR(errno);
      return err;
    }
#else
    err = UV_ENOTSUP;
    return err;
#endif
  }

  if (bind(fd, addr, addrlen)) {
    err = UV__ERR(errno);
    if (errno == EAFNOSUPPORT)
      /* OSX, other BSDs and SunoS fail with EAFNOSUPPORT when binding a
       * socket created with AF_INET to an AF_INET6 address or vice versa. */
      err = UV_EINVAL;
    return err;
  }

  if (addr->sa_family == AF_INET6)
    handle->flags |= UV_HANDLE_IPV6;

  handle->flags |= UV_HANDLE_BOUND;
  return 0;
}