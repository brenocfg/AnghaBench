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
struct sock_list {int /*<<< orphan*/  addr; scalar_t__ len; struct sock_list* next; } ;
struct regional {int dummy; } ;
typedef  scalar_t__ socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  log_assert (struct sock_list**) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,struct sockaddr_storage*,scalar_t__) ; 
 scalar_t__ regional_alloc (struct regional*,int) ; 

void sock_list_insert(struct sock_list** list, struct sockaddr_storage* addr,
	socklen_t len, struct regional* region)
{
	struct sock_list* add = (struct sock_list*)regional_alloc(region,
		sizeof(*add) - sizeof(add->addr) + (size_t)len);
	if(!add) {
		log_err("out of memory in socketlist insert");
		return;
	}
	log_assert(list);
	add->next = *list;
	add->len = len;
	*list = add;
	if(len) memmove(&add->addr, addr, len);
}