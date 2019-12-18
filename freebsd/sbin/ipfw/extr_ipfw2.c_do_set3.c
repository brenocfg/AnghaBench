#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int opcode; } ;
typedef  TYPE_1__ ip_fw3_opheader ;
struct TYPE_6__ {scalar_t__ test_only; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  EX_UNAVAILABLE ; 
 int /*<<< orphan*/  IPPROTO_IP ; 
 int /*<<< orphan*/  IPPROTO_RAW ; 
 int /*<<< orphan*/  IP_FW3 ; 
 int /*<<< orphan*/  SOCK_RAW ; 
 TYPE_4__ co ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int ipfw_socket ; 
 int setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,size_t) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
do_set3(int optname, ip_fw3_opheader *op3, size_t optlen)
{

	if (co.test_only)
		return (0);

	if (ipfw_socket == -1)
		ipfw_socket = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
	if (ipfw_socket < 0)
		err(EX_UNAVAILABLE, "socket");

	op3->opcode = optname;

	return (setsockopt(ipfw_socket, IPPROTO_IP, IP_FW3, op3, optlen));
}