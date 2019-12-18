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
typedef  scalar_t__ u_int32_t ;
struct thread {int dummy; } ;
struct sysent {scalar_t__ sy_thrcnt; } ;

/* Variables and functions */
 scalar_t__ SY_THR_INCR ; 
 scalar_t__ atomic_cmpset_rel_32 (scalar_t__*,scalar_t__,scalar_t__) ; 

void
_syscall_thread_exit(struct thread *td, struct sysent *se)
{
	u_int32_t cnt, oldcnt;

	do {
		oldcnt = se->sy_thrcnt;
		cnt = oldcnt - SY_THR_INCR;
	} while (atomic_cmpset_rel_32(&se->sy_thrcnt, oldcnt, cnt) == 0);
}