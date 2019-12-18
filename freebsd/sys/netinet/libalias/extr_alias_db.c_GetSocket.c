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
typedef  int u_short ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct libalias {int /*<<< orphan*/  sockCount; } ;
typedef  int /*<<< orphan*/  sock_addr ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  LIBALIAS_LOCK_ASSERT (struct libalias*) ; 
 int LINK_TCP ; 
 int LINK_UDP ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static		u_short
GetSocket(struct libalias *la, u_short port_net, int *sockfd, int link_type)
{
	int err;
	int sock;
	struct sockaddr_in sock_addr;

	LIBALIAS_LOCK_ASSERT(la);
	if (link_type == LINK_TCP)
		sock = socket(AF_INET, SOCK_STREAM, 0);
	else if (link_type == LINK_UDP)
		sock = socket(AF_INET, SOCK_DGRAM, 0);
	else {
#ifdef LIBALIAS_DEBUG
		fprintf(stderr, "PacketAlias/GetSocket(): ");
		fprintf(stderr, "incorrect link type\n");
#endif
		return (0);
	}

	if (sock < 0) {
#ifdef LIBALIAS_DEBUG
		fprintf(stderr, "PacketAlias/GetSocket(): ");
		fprintf(stderr, "socket() error %d\n", *sockfd);
#endif
		return (0);
	}
	sock_addr.sin_family = AF_INET;
	sock_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	sock_addr.sin_port = port_net;

	err = bind(sock,
	    (struct sockaddr *)&sock_addr,
	    sizeof(sock_addr));
	if (err == 0) {
		la->sockCount++;
		*sockfd = sock;
		return (1);
	} else {
		close(sock);
		return (0);
	}
}