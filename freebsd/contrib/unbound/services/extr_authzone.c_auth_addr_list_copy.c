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
struct auth_addr {struct auth_addr* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  auth_free_master_addrs (struct auth_addr*) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 scalar_t__ memdup (struct auth_addr*,int) ; 

__attribute__((used)) static struct auth_addr*
auth_addr_list_copy(struct auth_addr* source)
{
	struct auth_addr* list = NULL, *last = NULL;
	struct auth_addr* p;
	for(p=source; p; p=p->next) {
		struct auth_addr* a = (struct auth_addr*)memdup(p, sizeof(*p));
		if(!a) {
			log_err("malloc failure");
			auth_free_master_addrs(list);
			return NULL;
		}
		a->next = NULL;
		if(last) last->next = a;
		if(!list) list = a;
		last = a;
	}
	return list;
}