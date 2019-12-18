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
struct in_addr {void* s_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IP_MULTICAST_IF ; 
 int /*<<< orphan*/  WARN_SUCCESS ; 
 void* inet_addr (char*) ; 
 int /*<<< orphan*/  test_in_addr (int /*<<< orphan*/ ,char*,struct in_addr,struct in_addr,struct in_addr,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
test_if(int raw_sock, int tcp_sock, int udp_sock)
{
	struct in_addr defaultv, modifiedv, fakev;

	defaultv.s_addr = inet_addr("0.0.0.0");

	/* Should be valid on all hosts. */
	modifiedv.s_addr = inet_addr("127.0.0.1");

	/* Should not happen. */
	fakev.s_addr = inet_addr("255.255.255.255");

	test_in_addr(IP_MULTICAST_IF, "IP_MULTICAST_IF", defaultv, modifiedv,
	    fakev, "raw_sock", raw_sock, 0);
	test_in_addr(IP_MULTICAST_IF, "IP_MULTICAST_IF", defaultv, modifiedv,
	    fakev, "tcp_sock", tcp_sock, WARN_SUCCESS);
	test_in_addr(IP_MULTICAST_IF, "IP_MULTICAST_IF", defaultv, modifiedv,
	    fakev, "udp_sock", udp_sock, 0);
}