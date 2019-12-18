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
struct sock_list {scalar_t__ len; struct sock_list* next; int /*<<< orphan*/  addr; } ;
typedef  scalar_t__ socklen_t ;

/* Variables and functions */
 scalar_t__ sockaddr_cmp_addr (struct sockaddr_storage*,scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 

int sock_list_find(struct sock_list* list, struct sockaddr_storage* addr,
        socklen_t len)
{
	while(list) {
		if(len == list->len) {
			if(len == 0 || sockaddr_cmp_addr(addr, len, 
				&list->addr, list->len) == 0)
				return 1;
		}
		list = list->next;
	}
	return 0;
}