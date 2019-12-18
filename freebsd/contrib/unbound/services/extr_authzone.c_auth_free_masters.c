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
struct auth_master {struct auth_master* file; struct auth_master* host; int /*<<< orphan*/  list; struct auth_master* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  auth_free_master_addrs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct auth_master*) ; 

__attribute__((used)) static void
auth_free_masters(struct auth_master* list)
{
	struct auth_master* n;
	while(list) {
		n = list->next;
		auth_free_master_addrs(list->list);
		free(list->host);
		free(list->file);
		free(list);
		list = n;
	}
}