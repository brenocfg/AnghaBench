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
typedef  int /*<<< orphan*/  socklen_t ;
struct TYPE_2__ {scalar_t__ test_only; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  EX_UNAVAILABLE ; 
 int /*<<< orphan*/  IPPROTO_IP ; 
 int /*<<< orphan*/  IPPROTO_RAW ; 
 int IP_DUMMYNET_GET ; 
 int IP_FW3 ; 
 int IP_FW_ADD ; 
 int IP_FW_GET ; 
 int IP_FW_NAT_GET_CONFIG ; 
 int IP_FW_NAT_GET_LOG ; 
 int /*<<< orphan*/  SOCK_RAW ; 
 TYPE_1__ co ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int getsockopt (int,int /*<<< orphan*/ ,int,void*,int /*<<< orphan*/ *) ; 
 int ipfw_socket ; 
 int setsockopt (int,int /*<<< orphan*/ ,int,void*,uintptr_t) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
do_cmd(int optname, void *optval, uintptr_t optlen)
{
	int i;

	if (co.test_only)
		return 0;

	if (ipfw_socket == -1)
		ipfw_socket = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
	if (ipfw_socket < 0)
		err(EX_UNAVAILABLE, "socket");

	if (optname == IP_FW_GET || optname == IP_DUMMYNET_GET ||
	    optname == IP_FW_ADD || optname == IP_FW3 ||
	    optname == IP_FW_NAT_GET_CONFIG ||
	    optname < 0 ||
	    optname == IP_FW_NAT_GET_LOG) {
		if (optname < 0)
			optname = -optname;
		i = getsockopt(ipfw_socket, IPPROTO_IP, optname, optval,
			(socklen_t *)optlen);
	} else {
		i = setsockopt(ipfw_socket, IPPROTO_IP, optname, optval, optlen);
	}
	return i;
}