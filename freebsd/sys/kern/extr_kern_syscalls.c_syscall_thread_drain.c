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
typedef  int u_int32_t ;
struct sysent {int sy_thrcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  SY_THR_ABSENT ; 
 int SY_THR_DRAINING ; 
 int SY_THR_STATIC ; 
 scalar_t__ atomic_cmpset_32 (int*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_cmpset_acq_32 (int*,int,int) ; 
 int hz ; 
 int /*<<< orphan*/  pause (char*,int) ; 

__attribute__((used)) static void
syscall_thread_drain(struct sysent *se)
{
	u_int32_t cnt, oldcnt;

	do {
		oldcnt = se->sy_thrcnt;
		KASSERT((oldcnt & SY_THR_STATIC) == 0,
		    ("drain on static syscall"));
		cnt = oldcnt | SY_THR_DRAINING;
	} while (atomic_cmpset_acq_32(&se->sy_thrcnt, oldcnt, cnt) == 0);
	while (atomic_cmpset_32(&se->sy_thrcnt, SY_THR_DRAINING,
	    SY_THR_ABSENT) == 0)
		pause("scdrn", hz/2);
}