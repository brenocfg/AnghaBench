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
struct sockaddr_in {scalar_t__ sin_port; } ;
struct delegpt_addr {struct delegpt_addr* next_target; int /*<<< orphan*/  addr; int /*<<< orphan*/  addrlen; } ;
struct delegpt {struct delegpt_addr* target_list; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 scalar_t__ sockaddr_cmp_addr (struct sockaddr_storage*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct delegpt_addr*
delegpt_find_addr(struct delegpt* dp, struct sockaddr_storage* addr, 
	socklen_t addrlen)
{
	struct delegpt_addr* p = dp->target_list;
	while(p) {
		if(sockaddr_cmp_addr(addr, addrlen, &p->addr, p->addrlen)==0
			&& ((struct sockaddr_in*)addr)->sin_port ==
			   ((struct sockaddr_in*)&p->addr)->sin_port) {
			return p;
		}
		p = p->next_target;
	}
	return NULL;
}