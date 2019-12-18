#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* s_addr; } ;
struct TYPE_4__ {void* s_addr; } ;
struct ip_mreq {TYPE_1__ imr_interface; TYPE_2__ imr_multiaddr; } ;
typedef  int /*<<< orphan*/  imr ;

/* Variables and functions */
 int /*<<< orphan*/  DISC_IP ; 
 int /*<<< orphan*/  IPPROTO_IP ; 
 int /*<<< orphan*/  IP_ADD_MEMBERSHIP ; 
 int /*<<< orphan*/  MULTICAST_IP ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  bzero (struct ip_mreq*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 void* inet_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ip_mreq*,int) ; 
 int socket (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*,char const*,...) ; 

__attribute__((used)) static int
multicast_open(int *sockp, int type, const char *type_string)
{
	struct ip_mreq imr;
	int sock;

	sock = socket(PF_INET, type, 0);
	if (sock < 0) {
		warn("multicast_test: socket(PF_INET, %s, 0)", type_string);
		return (-1);
	}

	bzero(&imr, sizeof(imr));
	imr.imr_multiaddr.s_addr = inet_addr(MULTICAST_IP);
	imr.imr_interface.s_addr = inet_addr(DISC_IP);

	if (setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &imr,
	    sizeof(imr)) < 0) {
		warn("multicast_test: setsockopt(IPPROTO_IP, "
		    "IP_ADD_MEMBERSHIP, {%s, %s})", MULTICAST_IP, DISC_IP);
		close(sock);
		return (-1);
	}

	*sockp = sock;
	return (0);
}