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
struct thread {struct seltd* td_sel; } ;
struct seltd {int /*<<< orphan*/  st_mtx; int /*<<< orphan*/  st_wait; scalar_t__ st_free2; scalar_t__ st_free1; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_SELECT ; 
 int /*<<< orphan*/  cv_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct seltd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  selfd_zone ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,scalar_t__) ; 

void
seltdfini(struct thread *td)
{
	struct seltd *stp;

	stp = td->td_sel;
	if (stp == NULL)
		return;
	if (stp->st_free1)
		uma_zfree(selfd_zone, stp->st_free1);
	if (stp->st_free2)
		uma_zfree(selfd_zone, stp->st_free2);
	td->td_sel = NULL;
	cv_destroy(&stp->st_wait);
	mtx_destroy(&stp->st_mtx);
	free(stp, M_SELECT);
}