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
struct config_strlist {struct config_strlist* next; int /*<<< orphan*/  str; } ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

struct config_strlist*
cfg_strlist_find(struct config_strlist* head, const char *item)
{
	struct config_strlist *s = head;
	if(!head){
		return NULL;
	}
	while(s) {
		if(strcmp(s->str, item) == 0) {
			return s;
		}
		s = s->next;
	}
	return NULL;
}