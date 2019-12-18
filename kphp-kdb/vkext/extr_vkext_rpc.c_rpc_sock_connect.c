#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct pollfd {int fd; int /*<<< orphan*/  events; } ;
typedef  int /*<<< orphan*/  flags ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_CNT (int (*) (unsigned int,int,double)) ; 
 int /*<<< orphan*/  AF_INET ; 
 scalar_t__ EINPROGRESS ; 
 int /*<<< orphan*/  END_TIMER (int (*) (unsigned int,int,double)) ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int /*<<< orphan*/  POLLOUT ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_KEEPALIVE ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 int /*<<< orphan*/  START_TIMER (int (*) (unsigned int,int,double)) ; 
 int /*<<< orphan*/  TCP_NODELAY ; 
 int /*<<< orphan*/  close (int) ; 
 int connect (int,struct sockaddr*,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int get_ms_timeout (double) ; 
 int /*<<< orphan*/  htonl (unsigned int) ; 
 int /*<<< orphan*/  htons (int) ; 
 scalar_t__ poll (struct pollfd*,int,int) ; 
 int /*<<< orphan*/  setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rpc_sock_connect (unsigned host, int port, double timeout) { /* {{{ */
  ADD_CNT (rpc_sock_connect);
  START_TIMER (rpc_sock_connect);
  int sfd;
  if ((sfd = socket (AF_INET, SOCK_STREAM, 0)) == -1) {
    END_TIMER (rpc_sock_connect);
    return -1;
  }
  int flags = 1;
  setsockopt (sfd, SOL_SOCKET, SO_REUSEADDR, &flags, sizeof (flags));
  setsockopt (sfd, SOL_SOCKET, SO_KEEPALIVE, &flags, sizeof (flags));
  setsockopt (sfd, IPPROTO_TCP, TCP_NODELAY, &flags, sizeof (flags));
  struct sockaddr_in addr;
  
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  addr.sin_addr.s_addr = htonl (host);

  fcntl (sfd, F_SETFL, O_NONBLOCK);
  if (connect (sfd, (struct sockaddr *) &addr, sizeof (addr)) == -1) {
    if (errno != EINPROGRESS) {
      END_TIMER (rpc_sock_connect);
      close (sfd);
      return -1;
    }
  }

  struct pollfd s;
  s.fd = sfd;
  s.events = POLLOUT;

  int t = get_ms_timeout (timeout);

  if (poll (&s, 1, t) <= 0) {
    close (sfd);
    END_TIMER (rpc_sock_connect);
    return -1;
  }

  
  END_TIMER (rpc_sock_connect);
  return sfd;
}