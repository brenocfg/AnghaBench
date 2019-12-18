#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ pr_propname; int /*<<< orphan*/  pr_cbs; } ;
typedef  TYPE_1__ dsl_prop_record_t ;
struct TYPE_7__ {int /*<<< orphan*/  dd_props; } ;
typedef  TYPE_2__ dsl_dir_t ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 
 int /*<<< orphan*/  list_destroy (int /*<<< orphan*/ *) ; 
 TYPE_1__* list_remove_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strfree (char*) ; 

void
dsl_prop_fini(dsl_dir_t *dd)
{
	dsl_prop_record_t *pr;

	while ((pr = list_remove_head(&dd->dd_props)) != NULL) {
		list_destroy(&pr->pr_cbs);
		strfree((char *)pr->pr_propname);
		kmem_free(pr, sizeof (dsl_prop_record_t));
	}
	list_destroy(&dd->dd_props);
}