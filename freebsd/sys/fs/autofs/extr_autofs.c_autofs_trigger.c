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
struct autofs_node {scalar_t__ an_retries; } ;
struct TYPE_2__ {int /*<<< orphan*/  sc_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTOFS_DEBUG (char*,...) ; 
 int EINTR ; 
 int ERESTART ; 
 scalar_t__ autofs_retry_attempts ; 
 int autofs_retry_delay ; 
 TYPE_1__* autofs_softc ; 
 int autofs_trigger_one (struct autofs_node*,char const*,int) ; 
 int hz ; 
 int /*<<< orphan*/  pause (char*,int) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

int
autofs_trigger(struct autofs_node *anp,
    const char *component, int componentlen)
{
	int error;

	for (;;) {
		error = autofs_trigger_one(anp, component, componentlen);
		if (error == 0) {
			anp->an_retries = 0;
			return (0);
		}
		if (error == EINTR || error == ERESTART) {
			AUTOFS_DEBUG("trigger interrupted by signal, "
			    "not retrying");
			anp->an_retries = 0;
			return (error);
		}
		anp->an_retries++;
		if (anp->an_retries >= autofs_retry_attempts) {
			AUTOFS_DEBUG("trigger failed %d times; returning "
			    "error %d", anp->an_retries, error);
			anp->an_retries = 0;
			return (error);

		}
		AUTOFS_DEBUG("trigger failed with error %d; will retry in "
		    "%d seconds, %d attempts left", error, autofs_retry_delay,
		    autofs_retry_attempts - anp->an_retries);
		sx_xunlock(&autofs_softc->sc_lock);
		pause("autofs_retry", autofs_retry_delay * hz);
		sx_xlock(&autofs_softc->sc_lock);
	}
}