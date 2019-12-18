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
struct sockaddr_storage {int dummy; } ;
struct auth_addr {int /*<<< orphan*/  addrlen; int /*<<< orphan*/  addr; struct auth_addr* next; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 scalar_t__ sockaddr_cmp_addr (struct sockaddr_storage*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
addr_in_list(struct auth_addr* list, struct sockaddr_storage* addr,
	socklen_t addrlen)
{
	struct auth_addr* p;
	for(p=list; p; p=p->next) {
		if(sockaddr_cmp_addr(addr, addrlen, &p->addr, p->addrlen)==0)
			return 1;
	}
	return 0;
}