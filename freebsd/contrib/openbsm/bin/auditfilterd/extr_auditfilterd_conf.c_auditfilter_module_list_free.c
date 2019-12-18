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
struct auditfilter_module_list {int dummy; } ;
struct auditfilter_module {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_EMPTY (struct auditfilter_module_list*) ; 
 struct auditfilter_module* TAILQ_FIRST (struct auditfilter_module_list*) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (struct auditfilter_module_list*,struct auditfilter_module*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  am_list ; 
 int /*<<< orphan*/  auditfilter_module_free (struct auditfilter_module*) ; 

__attribute__((used)) static void
auditfilter_module_list_free(struct auditfilter_module_list *list)
{
	struct auditfilter_module *am;

	while (!(TAILQ_EMPTY(list))) {
		am = TAILQ_FIRST(list);
		TAILQ_REMOVE(list, am, am_list);
		auditfilter_module_free(am);
	}
}