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
typedef  int /*<<< orphan*/  dtrace_probedesc_t ;
struct TYPE_2__ {int /*<<< orphan*/ * pp_syscallnames; } ;

/* Variables and functions */
 int MAXSYSCALL ; 
 int /*<<< orphan*/  MODNAME ; 
 int /*<<< orphan*/  SYSTRACE_ARTIFICIAL_FRAMES ; 
 scalar_t__ SYSTRACE_ENTRY (int) ; 
 scalar_t__ SYSTRACE_RETURN (int) ; 
 int /*<<< orphan*/  dtrace_probe_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ dtrace_probe_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  systrace_id ; 
 TYPE_1__ uglyhack ; 

__attribute__((used)) static void
systrace_provide(void *arg, dtrace_probedesc_t *desc)
{
	int i;

	if (desc != NULL)
		return;

	for (i = 0; i < MAXSYSCALL; i++) {
		if (dtrace_probe_lookup(systrace_id, MODNAME,
		    uglyhack.pp_syscallnames[i], "entry") != 0)
			continue;

		(void)dtrace_probe_create(systrace_id, MODNAME,
		    uglyhack.pp_syscallnames[i], "entry",
		    SYSTRACE_ARTIFICIAL_FRAMES,
		    (void *)((uintptr_t)SYSTRACE_ENTRY(i)));
		(void)dtrace_probe_create(systrace_id, MODNAME,
		    uglyhack.pp_syscallnames[i], "return",
		    SYSTRACE_ARTIFICIAL_FRAMES,
		    (void *)((uintptr_t)SYSTRACE_RETURN(i)));
	}
}