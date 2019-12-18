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
typedef  int /*<<< orphan*/  yes ;
struct sockaddr_in {scalar_t__ sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  sockfd ;

/* Variables and functions */
 scalar_t__ AF_UNIX ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 int /*<<< orphan*/  SO_REUSEPORT ; 
 int UV__ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int getsockname (int,struct sockaddr*,unsigned int*) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int uv__set_reuse(int fd) {
  int yes;
  yes = 1;

#if defined(SO_REUSEPORT) && defined(__MVS__)
  struct sockaddr_in sockfd;
  unsigned int sockfd_len = sizeof(sockfd);
  if (getsockname(fd, (struct sockaddr*) &sockfd, &sockfd_len) == -1)
      return UV__ERR(errno);
  if (sockfd.sin_family == AF_UNIX) {
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)))
      return UV__ERR(errno);
  } else {
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &yes, sizeof(yes)))
       return UV__ERR(errno);
  }
#elif defined(SO_REUSEPORT) && !defined(__linux__)
  if (setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &yes, sizeof(yes)))
    return UV__ERR(errno);
#else
  if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)))
    return UV__ERR(errno);
#endif

  return 0;
}