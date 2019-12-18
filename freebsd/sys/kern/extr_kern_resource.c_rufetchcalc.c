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
struct timeval {int dummy; } ;
struct rusage {int dummy; } ;
struct proc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROC_STATLOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_STATUNLOCK (struct proc*) ; 
 int /*<<< orphan*/  calcru (struct proc*,struct timeval*,struct timeval*) ; 
 int /*<<< orphan*/  rufetch (struct proc*,struct rusage*) ; 

void
rufetchcalc(struct proc *p, struct rusage *ru, struct timeval *up,
    struct timeval *sp)
{

	PROC_STATLOCK(p);
	rufetch(p, ru);
	calcru(p, up, sp);
	PROC_STATUNLOCK(p);
}