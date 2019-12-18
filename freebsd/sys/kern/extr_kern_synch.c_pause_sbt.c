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
typedef  scalar_t__ sbintime_t ;

/* Variables and functions */
 int C_CATCH ; 
 int /*<<< orphan*/  DELAY (scalar_t__) ; 
 int EWOULDBLOCK ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  PCATCH ; 
 scalar_t__ SBT_1S ; 
 int /*<<< orphan*/  SBT_1US ; 
 scalar_t__ SCHEDULER_STOPPED () ; 
 int _sleep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,scalar_t__,scalar_t__,int) ; 
 scalar_t__ cold ; 
 size_t curcpu ; 
 int /*<<< orphan*/ * curthread ; 
 scalar_t__ howmany (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ kdb_active ; 
 int /*<<< orphan*/ * pause_wchan ; 
 int /*<<< orphan*/  thread0 ; 
 scalar_t__ tick_sbt ; 

int
pause_sbt(const char *wmesg, sbintime_t sbt, sbintime_t pr, int flags)
{
	KASSERT(sbt >= 0, ("pause_sbt: timeout must be >= 0"));

	/* silently convert invalid timeouts */
	if (sbt == 0)
		sbt = tick_sbt;

	if ((cold && curthread == &thread0) || kdb_active ||
	    SCHEDULER_STOPPED()) {
		/*
		 * We delay one second at a time to avoid overflowing the
		 * system specific DELAY() function(s):
		 */
		while (sbt >= SBT_1S) {
			DELAY(1000000);
			sbt -= SBT_1S;
		}
		/* Do the delay remainder, if any */
		sbt = howmany(sbt, SBT_1US);
		if (sbt > 0)
			DELAY(sbt);
		return (EWOULDBLOCK);
	}
	return (_sleep(&pause_wchan[curcpu], NULL,
	    (flags & C_CATCH) ? PCATCH : 0, wmesg, sbt, pr, flags));
}