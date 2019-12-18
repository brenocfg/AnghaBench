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
struct inst_rmrr_iter_args {struct dmar_unit* dmar; } ;
struct dmar_unit {int hw_gcmd; int unit; int /*<<< orphan*/  domains; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMAR_BARRIER_RMRR ; 
 int DMAR_GCMD_TE ; 
 int /*<<< orphan*/  DMAR_LOCK (struct dmar_unit*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  LIST_EMPTY (int /*<<< orphan*/ *) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  dmar_barrier_enter (struct dmar_unit*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmar_barrier_exit (struct dmar_unit*,int /*<<< orphan*/ ) ; 
 int dmar_enable_translation (struct dmar_unit*) ; 
 int /*<<< orphan*/  dmar_inst_rmrr_iter ; 
 int /*<<< orphan*/  dmar_iterate_tbl (int /*<<< orphan*/ ,struct inst_rmrr_iter_args*) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 

int
dmar_instantiate_rmrr_ctxs(struct dmar_unit *dmar)
{
	struct inst_rmrr_iter_args iria;
	int error;

	if (!dmar_barrier_enter(dmar, DMAR_BARRIER_RMRR))
		return (0);

	error = 0;
	iria.dmar = dmar;
	dmar_iterate_tbl(dmar_inst_rmrr_iter, &iria);
	DMAR_LOCK(dmar);
	if (!LIST_EMPTY(&dmar->domains)) {
		KASSERT((dmar->hw_gcmd & DMAR_GCMD_TE) == 0,
	    ("dmar%d: RMRR not handled but translation is already enabled",
		    dmar->unit));
		error = dmar_enable_translation(dmar);
		if (bootverbose) {
			if (error == 0) {
				printf("dmar%d: enabled translation\n",
				    dmar->unit);
			} else {
				printf("dmar%d: enabling translation failed, "
				    "error %d\n", dmar->unit, error);
			}
		}
	}
	dmar_barrier_exit(dmar, DMAR_BARRIER_RMRR);
	return (error);
}