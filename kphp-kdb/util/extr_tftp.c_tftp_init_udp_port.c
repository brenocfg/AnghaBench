#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  udp_type_t ;
struct TYPE_5__ {int fd; int our_port; scalar_t__ ev; void* extra; int /*<<< orphan*/ * type; int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {TYPE_3__ u; } ;
typedef  TYPE_1__ tftp_connection_t ;
typedef  int /*<<< orphan*/  opt ;

/* Variables and functions */
 int EVT_LEVEL ; 
 int EVT_READ ; 
 int EVT_SPEC ; 
 scalar_t__ Events ; 
 int /*<<< orphan*/  IPPROTO_IP ; 
 int /*<<< orphan*/  IPPROTO_IPV6 ; 
 int /*<<< orphan*/  IPV6_RECVPKTINFO ; 
 int /*<<< orphan*/  IP_PKTINFO ; 
 int MAX_EVENTS ; 
 int SM_IPV6 ; 
 int /*<<< orphan*/  U_IPV6 ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ check_udp_functions (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  epoll_insert (int,int) ; 
 int /*<<< orphan*/  epoll_sethandler (int,int,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  kprintf (char*,int) ; 
 int /*<<< orphan*/  server_receive_udp ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int tftp_init_udp_port (tftp_connection_t *c, int sfd, int port, udp_type_t *type, void *extra, int mode) {
  if (check_udp_functions (type) < 0) {
    return -1;
  }
  assert (sfd > 2 && sfd < MAX_EVENTS);
  int opt = 1;
  if (setsockopt (sfd, IPPROTO_IP, IP_PKTINFO, &opt, sizeof (opt)) < 0) {
    kprintf ("setsockopt for %d failed: %m\n", sfd);
  }
  if ((mode & SM_IPV6) && setsockopt (sfd, IPPROTO_IPV6, IPV6_RECVPKTINFO, &opt, sizeof (opt)) < 0) {
    kprintf ("setsockopt for %d failed: %m\n", sfd);
  }
  c->u.fd = sfd;
  c->u.flags = mode & SM_IPV6 ? U_IPV6 : 0;
  c->u.type = type;
  c->u.extra = extra;
  c->u.ev = Events + sfd;
  c->u.our_port = port;
  epoll_sethandler (sfd, -5, server_receive_udp, &c->u);
  epoll_insert (sfd, EVT_LEVEL | EVT_READ | EVT_SPEC);
  return 0;
}