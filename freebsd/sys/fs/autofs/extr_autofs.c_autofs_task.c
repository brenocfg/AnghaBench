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
struct autofs_request {int ar_wildcards; int ar_done; int ar_in_progress; int /*<<< orphan*/  ar_error; int /*<<< orphan*/  ar_path; int /*<<< orphan*/  ar_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  sc_lock; int /*<<< orphan*/  sc_cv; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTOFS_WARN (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ETIMEDOUT ; 
 TYPE_1__* autofs_softc ; 
 int /*<<< orphan*/  autofs_timeout ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
autofs_task(void *context, int pending)
{
	struct autofs_request *ar;

	ar = context;

	sx_xlock(&autofs_softc->sc_lock);
	AUTOFS_WARN("request %d for %s timed out after %d seconds",
	    ar->ar_id, ar->ar_path, autofs_timeout);
	/*
	 * XXX: EIO perhaps?
	 */
	ar->ar_error = ETIMEDOUT;
	ar->ar_wildcards = true;
	ar->ar_done = true;
	ar->ar_in_progress = false;
	cv_broadcast(&autofs_softc->sc_cv);
	sx_xunlock(&autofs_softc->sc_lock);
}