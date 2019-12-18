#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  dts_vstate; } ;
typedef  TYPE_2__ dtrace_state_t ;
struct TYPE_18__ {int /*<<< orphan*/  dtpd_name; int /*<<< orphan*/  dtpd_func; int /*<<< orphan*/  dtpd_mod; int /*<<< orphan*/  dtpd_provider; } ;
typedef  TYPE_3__ dtrace_probedesc_t ;
struct TYPE_19__ {int dten_ndesc; TYPE_5__** dten_desc; TYPE_1__* dten_vstate; struct TYPE_19__* dten_next; } ;
typedef  TYPE_4__ dtrace_enabling_t ;
struct TYPE_20__ {TYPE_3__ dted_probe; } ;
typedef  TYPE_5__ dtrace_ecbdesc_t ;
struct TYPE_16__ {TYPE_2__* dtvs_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ DTRACE_FUNCNAMELEN ; 
 scalar_t__ DTRACE_MODNAMELEN ; 
 scalar_t__ DTRACE_NAMELEN ; 
 scalar_t__ DTRACE_PROVNAMELEN ; 
 int ENOENT ; 
 int MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dtrace_enabling_addlike (TYPE_4__*,TYPE_5__*,TYPE_3__*) ; 
 TYPE_4__* dtrace_enabling_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dtrace_enabling_destroy (TYPE_4__*) ; 
 int dtrace_enabling_retain (TYPE_4__*) ; 
 int /*<<< orphan*/  dtrace_lock ; 
 TYPE_4__* dtrace_retained ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dtrace_enabling_replicate(dtrace_state_t *state, dtrace_probedesc_t *match,
    dtrace_probedesc_t *create)
{
	dtrace_enabling_t *new, *enab;
	int found = 0, err = ENOENT;

	ASSERT(MUTEX_HELD(&dtrace_lock));
	ASSERT(strlen(match->dtpd_provider) < DTRACE_PROVNAMELEN);
	ASSERT(strlen(match->dtpd_mod) < DTRACE_MODNAMELEN);
	ASSERT(strlen(match->dtpd_func) < DTRACE_FUNCNAMELEN);
	ASSERT(strlen(match->dtpd_name) < DTRACE_NAMELEN);

	new = dtrace_enabling_create(&state->dts_vstate);

	/*
	 * Iterate over all retained enablings, looking for enablings that
	 * match the specified state.
	 */
	for (enab = dtrace_retained; enab != NULL; enab = enab->dten_next) {
		int i;

		/*
		 * dtvs_state can only be NULL for helper enablings -- and
		 * helper enablings can't be retained.
		 */
		ASSERT(enab->dten_vstate->dtvs_state != NULL);

		if (enab->dten_vstate->dtvs_state != state)
			continue;

		/*
		 * Now iterate over each probe description; we're looking for
		 * an exact match to the specified probe description.
		 */
		for (i = 0; i < enab->dten_ndesc; i++) {
			dtrace_ecbdesc_t *ep = enab->dten_desc[i];
			dtrace_probedesc_t *pd = &ep->dted_probe;

			if (strcmp(pd->dtpd_provider, match->dtpd_provider))
				continue;

			if (strcmp(pd->dtpd_mod, match->dtpd_mod))
				continue;

			if (strcmp(pd->dtpd_func, match->dtpd_func))
				continue;

			if (strcmp(pd->dtpd_name, match->dtpd_name))
				continue;

			/*
			 * We have a winning probe!  Add it to our growing
			 * enabling.
			 */
			found = 1;
			dtrace_enabling_addlike(new, ep, create);
		}
	}

	if (!found || (err = dtrace_enabling_retain(new)) != 0) {
		dtrace_enabling_destroy(new);
		return (err);
	}

	return (0);
}