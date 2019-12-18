#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  dts_vstate; } ;
typedef  TYPE_1__ dtrace_state_t ;
typedef  int /*<<< orphan*/  dof_hdr_t ;
typedef  int /*<<< orphan*/  c ;
struct TYPE_7__ {int /*<<< orphan*/ * dta_enabling; TYPE_1__* dta_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  CE_NOTE ; 
 int /*<<< orphan*/  CE_WARN ; 
 int /*<<< orphan*/  CRED () ; 
 int /*<<< orphan*/  KDI_DTSET_DTRACE_ACTIVATE ; 
 int MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmn_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cpu_lock ; 
 TYPE_5__ dtrace_anon ; 
 int /*<<< orphan*/  dtrace_dof_destroy (int /*<<< orphan*/ *) ; 
 int dtrace_dof_options (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * dtrace_dof_property (char*) ; 
 int dtrace_dof_slurp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtrace_enabling_dump (int /*<<< orphan*/ *) ; 
 int dtrace_enabling_retain (int /*<<< orphan*/ *) ; 
 int dtrace_err_verbose ; 
 int /*<<< orphan*/  dtrace_lock ; 
 TYPE_1__* dtrace_state_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dtrace_state_destroy (TYPE_1__*) ; 
 scalar_t__ kdi_dtrace_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static void
dtrace_anon_property(void)
{
	int i, rv;
	dtrace_state_t *state;
	dof_hdr_t *dof;
	char c[32];		/* enough for "dof-data-" + digits */

	ASSERT(MUTEX_HELD(&dtrace_lock));
	ASSERT(MUTEX_HELD(&cpu_lock));

	for (i = 0; ; i++) {
		(void) snprintf(c, sizeof (c), "dof-data-%d", i);

		dtrace_err_verbose = 1;

		if ((dof = dtrace_dof_property(c)) == NULL) {
			dtrace_err_verbose = 0;
			break;
		}

#ifdef illumos
		/*
		 * We want to create anonymous state, so we need to transition
		 * the kernel debugger to indicate that DTrace is active.  If
		 * this fails (e.g. because the debugger has modified text in
		 * some way), we won't continue with the processing.
		 */
		if (kdi_dtrace_set(KDI_DTSET_DTRACE_ACTIVATE) != 0) {
			cmn_err(CE_NOTE, "kernel debugger active; anonymous "
			    "enabling ignored.");
			dtrace_dof_destroy(dof);
			break;
		}
#endif

		/*
		 * If we haven't allocated an anonymous state, we'll do so now.
		 */
		if ((state = dtrace_anon.dta_state) == NULL) {
			state = dtrace_state_create(NULL, NULL);
			dtrace_anon.dta_state = state;

			if (state == NULL) {
				/*
				 * This basically shouldn't happen:  the only
				 * failure mode from dtrace_state_create() is a
				 * failure of ddi_soft_state_zalloc() that
				 * itself should never happen.  Still, the
				 * interface allows for a failure mode, and
				 * we want to fail as gracefully as possible:
				 * we'll emit an error message and cease
				 * processing anonymous state in this case.
				 */
				cmn_err(CE_WARN, "failed to create "
				    "anonymous state");
				dtrace_dof_destroy(dof);
				break;
			}
		}

		rv = dtrace_dof_slurp(dof, &state->dts_vstate, CRED(),
		    &dtrace_anon.dta_enabling, 0, 0, B_TRUE);

		if (rv == 0)
			rv = dtrace_dof_options(dof, state);

		dtrace_err_verbose = 0;
		dtrace_dof_destroy(dof);

		if (rv != 0) {
			/*
			 * This is malformed DOF; chuck any anonymous state
			 * that we created.
			 */
			ASSERT(dtrace_anon.dta_enabling == NULL);
			dtrace_state_destroy(state);
			dtrace_anon.dta_state = NULL;
			break;
		}

		ASSERT(dtrace_anon.dta_enabling != NULL);
	}

	if (dtrace_anon.dta_enabling != NULL) {
		int rval;

		/*
		 * dtrace_enabling_retain() can only fail because we are
		 * trying to retain more enablings than are allowed -- but
		 * we only have one anonymous enabling, and we are guaranteed
		 * to be allowed at least one retained enabling; we assert
		 * that dtrace_enabling_retain() returns success.
		 */
		rval = dtrace_enabling_retain(dtrace_anon.dta_enabling);
		ASSERT(rval == 0);

		dtrace_enabling_dump(dtrace_anon.dta_enabling);
	}
}