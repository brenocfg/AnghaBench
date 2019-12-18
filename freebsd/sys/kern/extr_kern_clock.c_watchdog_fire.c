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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ u_long ;

/* Variables and functions */
 int /*<<< orphan*/  KDB_WHY_WATCHDOG ; 
 scalar_t__* intrcnt ; 
 char* intrnames ; 
 int /*<<< orphan*/  kdb_backtrace () ; 
 int /*<<< orphan*/  kdb_enter (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int sintrcnt ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static void
watchdog_fire(void)
{
	int nintr;
	uint64_t inttotal;
	u_long *curintr;
	char *curname;

	curintr = intrcnt;
	curname = intrnames;
	inttotal = 0;
	nintr = sintrcnt / sizeof(u_long);

	printf("interrupt                   total\n");
	while (--nintr >= 0) {
		if (*curintr)
			printf("%-12s %20lu\n", curname, *curintr);
		curname += strlen(curname) + 1;
		inttotal += *curintr++;
	}
	printf("Total        %20ju\n", (uintmax_t)inttotal);

#if defined(KDB) && !defined(KDB_UNATTENDED)
	kdb_backtrace();
	kdb_enter(KDB_WHY_WATCHDOG, "watchdog timeout");
#else
	panic("watchdog timeout");
#endif
}