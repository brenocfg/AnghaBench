#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  section; } ;
struct pt_section_list {TYPE_1__ section; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct pt_section_list*) ; 
 int /*<<< orphan*/  pt_msec_fini (TYPE_1__*) ; 
 int /*<<< orphan*/  pt_section_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pt_section_list_free(struct pt_section_list *list)
{
	if (!list)
		return;

	pt_section_put(list->section.section);
	pt_msec_fini(&list->section);
	free(list);
}