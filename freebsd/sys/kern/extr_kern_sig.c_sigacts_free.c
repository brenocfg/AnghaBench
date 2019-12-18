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
struct sigacts {int /*<<< orphan*/  ps_mtx; int /*<<< orphan*/  ps_refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_SUBPROC ; 
 int /*<<< orphan*/  free (struct sigacts*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ refcount_release (int /*<<< orphan*/ *) ; 

void
sigacts_free(struct sigacts *ps)
{

	if (refcount_release(&ps->ps_refcnt) == 0)
		return;
	mtx_destroy(&ps->ps_mtx);
	free(ps, M_SUBPROC);
}