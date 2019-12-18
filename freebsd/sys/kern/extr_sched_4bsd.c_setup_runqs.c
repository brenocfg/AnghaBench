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
 int MAXCPU ; 
 int /*<<< orphan*/  runq ; 
 int /*<<< orphan*/  runq_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * runq_pcpu ; 

__attribute__((used)) static void
setup_runqs(void)
{
#ifdef SMP
	int i;

	for (i = 0; i < MAXCPU; ++i)
		runq_init(&runq_pcpu[i]);
#endif

	runq_init(&runq);
}