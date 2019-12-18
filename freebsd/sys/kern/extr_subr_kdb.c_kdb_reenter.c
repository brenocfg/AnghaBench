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
 int /*<<< orphan*/  kdb_active ; 
 int /*<<< orphan*/  kdb_backtrace () ; 
 int /*<<< orphan*/ * kdb_jmpbufp ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

void
kdb_reenter(void)
{

	if (!kdb_active || kdb_jmpbufp == NULL)
		return;

	printf("KDB: reentering\n");
	kdb_backtrace();
	longjmp(kdb_jmpbufp, 1);
	/* NOTREACHED */
}