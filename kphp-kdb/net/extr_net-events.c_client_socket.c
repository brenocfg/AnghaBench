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
typedef  int /*<<< orphan*/  in_addr_t ;
typedef  int /*<<< orphan*/  flags ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 scalar_t__ EINPROGRESS ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  IP_RECVERR ; 
 int SM_IPV6 ; 
 int SM_UDP ; 
 int /*<<< orphan*/  SOL_IP ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_KEEPALIVE ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 int /*<<< orphan*/  TCP_NODELAY ; 
 int /*<<< orphan*/  close (int) ; 
 int connect (int,struct sockaddr*,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  maximize_rcvbuf (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maximize_sndbuf (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 int new_socket (int,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ tcp_maximize_buffers ; 

int client_socket (in_addr_t in_addr, int port, int mode) {
  int sfd;
  struct sockaddr_in addr;
  int flags = 1;

  if (mode & SM_IPV6) {
    return -1;
  }

  if ((sfd = new_socket (mode, 1)) == -1) {
    return -1;
  }

  if (mode & SM_UDP) {
    maximize_sndbuf (sfd, 0);
    maximize_rcvbuf (sfd, 0);
    setsockopt (sfd, SOL_IP, IP_RECVERR, &flags, sizeof (flags));
  } else {
    setsockopt (sfd, SOL_SOCKET, SO_REUSEADDR, &flags, sizeof (flags));
    if (tcp_maximize_buffers) {
      maximize_sndbuf (sfd, 0);
      maximize_rcvbuf (sfd, 0);
    }
    setsockopt (sfd, SOL_SOCKET, SO_KEEPALIVE, &flags, sizeof (flags));
    setsockopt (sfd, IPPROTO_TCP, TCP_NODELAY, &flags, sizeof (flags));
  }

  memset (&addr, 0, sizeof (addr));

  addr.sin_family = AF_INET;
  addr.sin_port = htons (port);
  addr.sin_addr.s_addr = in_addr;
 
  if (connect (sfd, (struct sockaddr *) &addr, sizeof (addr)) == -1 && errno != EINPROGRESS) {
    perror ("connect()");
    close (sfd);
    return -1;
  }

  return sfd;

}