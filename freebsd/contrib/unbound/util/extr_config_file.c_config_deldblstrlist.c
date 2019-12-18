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
struct config_str2list {struct config_str2list* str2; struct config_str2list* str; struct config_str2list* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct config_str2list*) ; 

void
config_deldblstrlist(struct config_str2list* p)
{
	struct config_str2list *np;
	while(p) {
		np = p->next;
		free(p->str);
		free(p->str2);
		free(p);
		p = np;
	}
}