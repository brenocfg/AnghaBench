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
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  IPPROTO_IPV6 ; 
 int /*<<< orphan*/  IPV6_V6ONLY ; 
 int O_NONBLOCK ; 
 int SM_IPV6 ; 
 int SM_IPV6_ONLY ; 
 int SM_UDP ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  close (int) ; 
 int fcntl (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int new_socket (int mode, int nonblock) {
  int sfd;
  int flags;

  if ((sfd = socket (mode & SM_IPV6 ? AF_INET6 : AF_INET, mode & SM_UDP ? SOCK_DGRAM : SOCK_STREAM, 0)) == -1) {
    perror ("socket()");
    return -1;
  }

  if (mode & SM_IPV6) {
    flags = (mode & SM_IPV6_ONLY) != 0;
    if (setsockopt (sfd, IPPROTO_IPV6, IPV6_V6ONLY, &flags, 4) < 0) {
      perror ("setting IPV6_V6ONLY");
      close (sfd);
      return -1;
    }
  }

  if (!nonblock) {
    return sfd;
  }

  if ((flags = fcntl (sfd, F_GETFL, 0)) < 0 || fcntl (sfd, F_SETFL, flags | O_NONBLOCK) < 0) {
    perror ("setting O_NONBLOCK");
    close (sfd);
    return -1;
  }
  return sfd;
}