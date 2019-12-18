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
struct in_addr {scalar_t__ s_addr; } ;
struct TYPE_2__ {scalar_t__ s_addr; } ;
struct host_list {TYPE_1__ addr; struct host_list* next; } ;

/* Variables and functions */
 struct host_list* hosts ; 

__attribute__((used)) static int
search_host(struct in_addr addr)
{
	struct host_list *hp;

	if (!hosts)
		return(0);

	for (hp = hosts; hp != NULL; hp = hp->next) {
		if (hp->addr.s_addr == addr.s_addr)
			return(1);
	}
	return(0);
}