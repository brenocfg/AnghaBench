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

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 scalar_t__ EINVAL ; 
 int SOCK_STREAM ; 
 int UV__ERR (scalar_t__) ; 
 int UV__F_NONBLOCK ; 
 int UV__SOCK_CLOEXEC ; 
 scalar_t__ errno ; 
 scalar_t__ socketpair (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  uv__cloexec (int,int) ; 
 int /*<<< orphan*/  uv__nonblock (int,int) ; 

int uv__make_socketpair(int fds[2], int flags) {
#if defined(__linux__)
  static int no_cloexec;

  if (no_cloexec)
    goto skip;

  if (socketpair(AF_UNIX, SOCK_STREAM | UV__SOCK_CLOEXEC | flags, 0, fds) == 0)
    return 0;

  /* Retry on EINVAL, it means SOCK_CLOEXEC is not supported.
   * Anything else is a genuine error.
   */
  if (errno != EINVAL)
    return UV__ERR(errno);

  no_cloexec = 1;

skip:
#endif

  if (socketpair(AF_UNIX, SOCK_STREAM, 0, fds))
    return UV__ERR(errno);

  uv__cloexec(fds[0], 1);
  uv__cloexec(fds[1], 1);

  if (flags & UV__F_NONBLOCK) {
    uv__nonblock(fds[0], 1);
    uv__nonblock(fds[1], 1);
  }

  return 0;
}