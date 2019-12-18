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
struct TYPE_5__ {int /*<<< orphan*/  sa_family; } ;
struct TYPE_4__ {TYPE_2__ s; } ;
struct skt {int len; TYPE_1__ sktaddr; } ;
struct get_neigh_handler {int /*<<< orphan*/  oif; int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
typedef  int /*<<< orphan*/  addr_src ;

/* Variables and functions */
 int /*<<< orphan*/  EADDRNOTAVAIL ; 
 int /*<<< orphan*/  PORT_DISCARD ; 
 int SOCK_CLOEXEC ; 
 int SOCK_DGRAM ; 
 int bind (int,TYPE_2__*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  memset (struct skt*,int /*<<< orphan*/ ,int) ; 
 int nl_addr_fill_sockaddr (int /*<<< orphan*/ ,TYPE_2__*,int*) ; 
 int set_link_port (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int socket (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int create_socket(struct get_neigh_handler *neigh_handler,
			 struct skt *addr_dst, int *psock_fd)
{
	int err;
	struct skt addr_src;
	int sock_fd;

	memset(addr_dst, 0, sizeof(*addr_dst));
	memset(&addr_src, 0, sizeof(addr_src));
	addr_src.len = sizeof(addr_src.sktaddr);

	err = nl_addr_fill_sockaddr(neigh_handler->src,
				    &addr_src.sktaddr.s,
				    &addr_src.len);
	if (err) {
		errno = EADDRNOTAVAIL;
		return -1;
	}

	addr_dst->len = sizeof(addr_dst->sktaddr);
	err = nl_addr_fill_sockaddr(neigh_handler->dst,
				    &addr_dst->sktaddr.s,
				    &addr_dst->len);
	if (err) {
		errno = EADDRNOTAVAIL;
		return -1;
	}

	err = set_link_port(&addr_dst->sktaddr, PORT_DISCARD,
			    neigh_handler->oif);
	if (err)
		return -1;

	sock_fd = socket(addr_dst->sktaddr.s.sa_family,
			 SOCK_DGRAM | SOCK_CLOEXEC, 0);
	if (sock_fd == -1)
		return -1;
	err = bind(sock_fd, &addr_src.sktaddr.s, addr_src.len);
	if (err) {
		close(sock_fd);
		return -1;
	}

	*psock_fd = sock_fd;

	return 0;
}