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
struct TYPE_2__ {int /*<<< orphan*/  si_note; } ;
struct fuse_data {scalar_t__ ref; int /*<<< orphan*/  ms_mtx; TYPE_1__ ks_rsel; int /*<<< orphan*/  aw_mtx; int /*<<< orphan*/  daemoncred; int /*<<< orphan*/  rename_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  M_FUSEMSG ; 
 int /*<<< orphan*/  crfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  free (struct fuse_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  knlist_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  knlist_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_destroy (int /*<<< orphan*/ *) ; 

void
fdata_trydestroy(struct fuse_data *data)
{
	data->ref--;
	MPASS(data->ref >= 0);
	if (data->ref != 0)
		return;

	/* Driving off stage all that stuff thrown at device... */
	sx_destroy(&data->rename_lock);
	crfree(data->daemoncred);
	mtx_destroy(&data->aw_mtx);
	knlist_delete(&data->ks_rsel.si_note, curthread, 0);
	knlist_destroy(&data->ks_rsel.si_note);
	mtx_destroy(&data->ms_mtx);

	free(data, M_FUSEMSG);
}