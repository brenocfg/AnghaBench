#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ttl ;
struct TYPE_6__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_5__ {void* s_addr; } ;
struct TYPE_4__ {void* s_addr; } ;
struct sockaddr_in {TYPE_3__ imr_multiaddr; TYPE_2__ imr_interface; int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct ip_mreq {TYPE_3__ imr_multiaddr; TYPE_2__ imr_interface; int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
typedef  int /*<<< orphan*/  on ;
typedef  int /*<<< orphan*/  mcast_addr ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  IPPROTO_IP ; 
 int /*<<< orphan*/  IP_ADD_MEMBERSHIP ; 
 int /*<<< orphan*/  IP_MULTICAST_TTL ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 int /*<<< orphan*/  UPNP_MULTICAST_ADDRESS ; 
 int /*<<< orphan*/  UPNP_MULTICAST_PORT ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ssdp_listener_open(void)
{
	struct sockaddr_in addr;
	struct ip_mreq mcast_addr;
	int on = 1;
	/* per UPnP spec, keep IP packet time to live (TTL) small */
	unsigned char ttl = 4;
	int sd;

	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sd < 0 ||
	    fcntl(sd, F_SETFL, O_NONBLOCK) != 0 ||
	    setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)))
		goto fail;
	os_memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(UPNP_MULTICAST_PORT);
	if (bind(sd, (struct sockaddr *) &addr, sizeof(addr)))
		goto fail;
	os_memset(&mcast_addr, 0, sizeof(mcast_addr));
	mcast_addr.imr_interface.s_addr = htonl(INADDR_ANY);
	mcast_addr.imr_multiaddr.s_addr = inet_addr(UPNP_MULTICAST_ADDRESS);
	if (setsockopt(sd, IPPROTO_IP, IP_ADD_MEMBERSHIP,
		       (char *) &mcast_addr, sizeof(mcast_addr)) ||
	    setsockopt(sd, IPPROTO_IP, IP_MULTICAST_TTL,
		       &ttl, sizeof(ttl)))
		goto fail;

	return sd;

fail:
	if (sd >= 0)
		close(sd);
	return -1;
}