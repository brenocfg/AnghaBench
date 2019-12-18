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
 int /*<<< orphan*/  free (struct auth_addr*) ; 

__attribute__((used)) static void
auth_free_master_addrs(struct auth_addr* list)
{
	struct auth_addr *n;
	while(list) {
		n = list->next;
		free(list);
		list = n;
	}
}