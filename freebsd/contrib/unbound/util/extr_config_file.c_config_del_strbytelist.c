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
struct config_strbytelist {struct config_strbytelist* str2; struct config_strbytelist* str; struct config_strbytelist* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct config_strbytelist*) ; 

void
config_del_strbytelist(struct config_strbytelist* p)
{
	struct config_strbytelist* np;
	while(p) {
		np = p->next;
		free(p->str);
		free(p->str2);
		free(p);
		p = np;
	}
}