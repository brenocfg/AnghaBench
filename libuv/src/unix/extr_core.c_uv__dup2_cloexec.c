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
 scalar_t__ EBUSY ; 
 scalar_t__ EINVAL ; 
 scalar_t__ ENOSYS ; 
 int /*<<< orphan*/  F_DUP2FD_CLOEXEC ; 
 int /*<<< orphan*/  O_CLOEXEC ; 
 int UV__ERR (scalar_t__) ; 
 int dup2 (int,int) ; 
 int dup3 (int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int fcntl (int,int /*<<< orphan*/ ,int) ; 
 int uv__cloexec (int,int) ; 
 int /*<<< orphan*/  uv__close (int) ; 
 int uv__dup3 (int,int,int /*<<< orphan*/ ) ; 

int uv__dup2_cloexec(int oldfd, int newfd) {
  int r;
#if (defined(__FreeBSD__) && __FreeBSD__ >= 10) || defined(__NetBSD__)
  r = dup3(oldfd, newfd, O_CLOEXEC);
  if (r == -1)
    return UV__ERR(errno);
  return r;
#elif defined(__FreeBSD__) && defined(F_DUP2FD_CLOEXEC)
  r = fcntl(oldfd, F_DUP2FD_CLOEXEC, newfd);
  if (r != -1)
    return r;
  if (errno != EINVAL)
    return UV__ERR(errno);
  /* Fall through. */
#elif defined(__linux__)
  static int no_dup3;
  if (!no_dup3) {
    do
      r = uv__dup3(oldfd, newfd, O_CLOEXEC);
    while (r == -1 && errno == EBUSY);
    if (r != -1)
      return r;
    if (errno != ENOSYS)
      return UV__ERR(errno);
    /* Fall through. */
    no_dup3 = 1;
  }
#endif
  {
    int err;
    do
      r = dup2(oldfd, newfd);
#if defined(__linux__)
    while (r == -1 && errno == EBUSY);
#else
    while (0);  /* Never retry. */
#endif

    if (r == -1)
      return UV__ERR(errno);

    err = uv__cloexec(newfd, 1);
    if (err) {
      uv__close(newfd);
      return err;
    }

    return r;
  }
}