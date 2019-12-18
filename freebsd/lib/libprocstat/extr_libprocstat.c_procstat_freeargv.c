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
struct procstat {int /*<<< orphan*/ * argv; } ;

/* Variables and functions */
 int /*<<< orphan*/  argvec_free (int /*<<< orphan*/ *) ; 

void
procstat_freeargv(struct procstat *procstat)
{

	if (procstat->argv != NULL) {
		argvec_free(procstat->argv);
		procstat->argv = NULL;
	}
}