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
struct auth_master {int /*<<< orphan*/ * list; struct auth_master* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  auth_free_master_addrs (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
xfr_masterlist_free_addrs(struct auth_master* list)
{
	struct auth_master* m;
	for(m=list; m; m=m->next) {
		if(m->list) {
			auth_free_master_addrs(m->list);
			m->list = NULL;
		}
	}
}