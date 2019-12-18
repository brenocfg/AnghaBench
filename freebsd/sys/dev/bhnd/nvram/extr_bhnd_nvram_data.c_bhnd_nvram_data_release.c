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
struct bhnd_nvram_data {TYPE_1__* cls; int /*<<< orphan*/  refs; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* op_free ) (struct bhnd_nvram_data*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  bhnd_nv_free (struct bhnd_nvram_data*) ; 
 int /*<<< orphan*/  refcount_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct bhnd_nvram_data*) ; 

void
bhnd_nvram_data_release(struct bhnd_nvram_data *nv)
{
	if (!refcount_release(&nv->refs))
		return;

	/* Free any internal resources */
	nv->cls->op_free(nv);

	/* Free the instance allocation */
	bhnd_nv_free(nv);
}