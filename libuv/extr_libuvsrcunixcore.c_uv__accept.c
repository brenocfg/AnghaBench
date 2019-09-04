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
 scalar_t__ EINTR ; 
 scalar_t__ ENOSYS ; 
 int UV__ERR (scalar_t__) ; 
 int UV__SOCK_CLOEXEC ; 
 int UV__SOCK_NONBLOCK ; 
 int accept (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ errno ; 
 int uv__accept4 (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int uv__cloexec (int,int) ; 
 int /*<<< orphan*/  uv__close (int) ; 
 int uv__nonblock (int,int) ; 

int uv__accept(int sockfd) {
  int peerfd;
  int err;

  assert(sockfd >= 0);

  while (1) {
#if defined(__linux__)                          || \
    (defined(__FreeBSD__) && __FreeBSD__ >= 10) || \
    defined(__NetBSD__)
    static int no_accept4;

    if (no_accept4)
      goto skip;

    peerfd = uv__accept4(sockfd,
                         NULL,
                         NULL,
                         UV__SOCK_NONBLOCK|UV__SOCK_CLOEXEC);
    if (peerfd != -1)
      return peerfd;

    if (errno == EINTR)
      continue;

    if (errno != ENOSYS)
      return UV__ERR(errno);

    no_accept4 = 1;
skip:
#endif

    peerfd = accept(sockfd, NULL, NULL);
    if (peerfd == -1) {
      if (errno == EINTR)
        continue;
      return UV__ERR(errno);
    }

    err = uv__cloexec(peerfd, 1);
    if (err == 0)
      err = uv__nonblock(peerfd, 1);

    if (err) {
      uv__close(peerfd);
      return err;
    }

    return peerfd;
  }
}