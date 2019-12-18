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
struct TYPE_2__ {int cpuid; int /*<<< orphan*/  cpu_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_ENABLE ; 
 int MAXCPU ; 
 int /*<<< orphan*/  MUTEX_DEFAULT ; 
 int NANOSEC ; 
 int /*<<< orphan*/  cpu_lock ; 
 int hz ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int nsec_per_tick ; 
 TYPE_1__* solaris_cpu ; 

__attribute__((used)) static void
opensolaris_load(void *dummy)
{
	int i;

	/*
	 * "Enable" all CPUs even though they may not exist just so
	 * that the asserts work. On FreeBSD, if a CPU exists, it is
	 * enabled.
	 */
	for (i = 0; i < MAXCPU; i++) {
		solaris_cpu[i].cpuid = i;
		solaris_cpu[i].cpu_flags &= CPU_ENABLE;
	}

	mutex_init(&cpu_lock, "OpenSolaris CPU lock", MUTEX_DEFAULT, NULL);

	nsec_per_tick = NANOSEC / hz;
}