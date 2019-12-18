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
typedef  int /*<<< orphan*/  dtrace_state_t ;
typedef  int /*<<< orphan*/  dtrace_enabling_t ;
struct TYPE_2__ {int /*<<< orphan*/  dta_beganon; int /*<<< orphan*/ * dta_enabling; int /*<<< orphan*/ * dta_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  cpu_lock ; 
 TYPE_1__ dtrace_anon ; 
 int /*<<< orphan*/  dtrace_anon_property () ; 
 int /*<<< orphan*/  dtrace_enabling_match (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dtrace_enabling_provide (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dtrace_lock ; 
 int /*<<< orphan*/  dtrace_provider_lock ; 
 int /*<<< orphan*/ * dtrace_retained ; 
 int /*<<< orphan*/  dtrace_state_go (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dtrace_anon_init(void *dummy)
{
	dtrace_state_t *state = NULL;
	dtrace_enabling_t *enab;

	mutex_enter(&cpu_lock);
	mutex_enter(&dtrace_provider_lock);
	mutex_enter(&dtrace_lock);

	dtrace_anon_property();

	mutex_exit(&cpu_lock);

	/*
	 * If there are already providers, we must ask them to provide their
	 * probes, and then match any anonymous enabling against them.  Note
	 * that there should be no other retained enablings at this time:
	 * the only retained enablings at this time should be the anonymous
	 * enabling.
	 */
	if (dtrace_anon.dta_enabling != NULL) {
		ASSERT(dtrace_retained == dtrace_anon.dta_enabling);

		dtrace_enabling_provide(NULL);
		state = dtrace_anon.dta_state;

		/*
		 * We couldn't hold cpu_lock across the above call to
		 * dtrace_enabling_provide(), but we must hold it to actually
		 * enable the probes.  We have to drop all of our locks, pick
		 * up cpu_lock, and regain our locks before matching the
		 * retained anonymous enabling.
		 */
		mutex_exit(&dtrace_lock);
		mutex_exit(&dtrace_provider_lock);

		mutex_enter(&cpu_lock);
		mutex_enter(&dtrace_provider_lock);
		mutex_enter(&dtrace_lock);

		if ((enab = dtrace_anon.dta_enabling) != NULL)
			(void) dtrace_enabling_match(enab, NULL);

		mutex_exit(&cpu_lock);
	}

	mutex_exit(&dtrace_provider_lock);
	mutex_exit(&dtrace_lock);

	if (state != NULL) {
		/*
		 * If we created any anonymous state, set it going now.
		 */
		(void) dtrace_state_go(state, &dtrace_anon.dta_beganon);
	}
}