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

/* Variables and functions */
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
usage(void)
{

	printf("j mcast-addr ifname [src-addr] - join IP multicast group\n");
	printf("l mcast-addr ifname [src-addr] - leave IP multicast group\n");
	printf(
"i mcast-addr ifname n          - set n include mode src filter\n");
	printf(
"e mcast-addr ifname n          - set n exclude mode src filter\n");
	printf("t mcast-addr ifname src-addr  - allow traffic from src\n");
	printf("b mcast-addr ifname src-addr  - block traffic from src\n");
	printf("g mcast-addr ifname n        - get and show n src filters\n");
	printf("a ifname mac-addr          - add link multicast filter\n");
	printf("d ifname mac-addr          - delete link multicast filter\n");
	printf("m ifname 1/0               - set/clear ether allmulti flag\n");
	printf("p ifname 1/0               - set/clear ether promisc flag\n");
	printf("f filename                 - read command(s) from file\n");
	printf("s seconds                  - sleep for some time\n");
	printf("q                          - quit\n");
}