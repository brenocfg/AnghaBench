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
struct config_collate_arg {int status; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  cfg_strlist_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strdup (char*) ; 

void config_collate_func(char* line, void* arg)
{
	struct config_collate_arg* m = (struct config_collate_arg*)arg;
	if(m->status)
		return;
	if(!cfg_strlist_append(&m->list, strdup(line)))
		m->status = 1;
}