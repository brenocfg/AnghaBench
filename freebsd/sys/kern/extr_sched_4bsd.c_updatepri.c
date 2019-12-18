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
struct thread {int dummy; } ;
struct td_sched {int ts_slptime; unsigned int ts_estcpu; } ;
typedef  int fixpt_t ;
struct TYPE_2__ {int /*<<< orphan*/ * ldavg; } ;

/* Variables and functions */
 TYPE_1__ averunnable ; 
 unsigned int decay_cpu (int,unsigned int) ; 
 int loadfactor (int /*<<< orphan*/ ) ; 
 struct td_sched* td_get_sched (struct thread*) ; 

__attribute__((used)) static void
updatepri(struct thread *td)
{
	struct td_sched *ts;
	fixpt_t loadfac;
	unsigned int newcpu;

	ts = td_get_sched(td);
	loadfac = loadfactor(averunnable.ldavg[0]);
	if (ts->ts_slptime > 5 * loadfac)
		ts->ts_estcpu = 0;
	else {
		newcpu = ts->ts_estcpu;
		ts->ts_slptime--;	/* was incremented in schedcpu() */
		while (newcpu && --ts->ts_slptime)
			newcpu = decay_cpu(loadfac, newcpu);
		ts->ts_estcpu = newcpu;
	}
}