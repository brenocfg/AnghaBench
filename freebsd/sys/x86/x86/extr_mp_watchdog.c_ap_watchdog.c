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
typedef  int u_int ;
struct proc {char* p_comm; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  KDB_WHY_WATCHDOG ; 
 int MAXCOMLEN ; 
 int /*<<< orphan*/  atomic_subtract_int (int*,int) ; 
 int /*<<< orphan*/  bcopy (char*,char*,int) ; 
 struct proc* curproc ; 
 int /*<<< orphan*/  kdb_enter (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int watchdog_cpu ; 
 int watchdog_dontfire ; 
 int /*<<< orphan*/  watchdog_ipi_nmi () ; 
 scalar_t__ watchdog_nmi ; 
 int watchdog_timer ; 

void
ap_watchdog(u_int cpuid)
{
	char old_pcomm[MAXCOMLEN + 1];
	struct proc *p;

	if (watchdog_cpu != cpuid)
		return;

	printf("watchdog started on cpu %d\n", cpuid);
	p = curproc;
	bcopy(p->p_comm, old_pcomm, MAXCOMLEN + 1);
	snprintf(p->p_comm, MAXCOMLEN + 1, "mp_watchdog cpu %d", cpuid);
	while (1) {
		DELAY(1000000);				/* One second. */
		if (watchdog_cpu != cpuid)
			break;
		atomic_subtract_int(&watchdog_timer, 1);
		if (watchdog_timer < 4)
			printf("Watchdog timer: %d\n", watchdog_timer);
		if (watchdog_timer == 0 && watchdog_dontfire == 0) {
			printf("Watchdog firing!\n");
			watchdog_dontfire = 1;
			if (watchdog_nmi)
				watchdog_ipi_nmi();
			else
				kdb_enter(KDB_WHY_WATCHDOG, "mp_watchdog");
		}
	}
	bcopy(old_pcomm, p->p_comm, MAXCOMLEN + 1);
	printf("watchdog stopped on cpu %d\n", cpuid);
}