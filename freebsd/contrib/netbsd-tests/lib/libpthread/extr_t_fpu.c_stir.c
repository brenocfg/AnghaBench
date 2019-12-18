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

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE_MSG (int,char*,int /*<<< orphan*/ ) ; 
 double cos (double) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ sched_yield () ; 
 double sin (double) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *
stir(void *p)
{
	double *q = (double *)p;
	double x = *q++;
	double y = *q++;
	double z = *q++;

	for (;;) {
		x = sin ((y = cos (x + y + .4)) - (z = cos (x + z + .6)));
		ATF_REQUIRE_MSG(sched_yield() == 0,
		    "sched_yield failed: %s", strerror(errno));
	}
}