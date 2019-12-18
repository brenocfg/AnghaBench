#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct thread {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  data; scalar_t__ level_type; int /*<<< orphan*/  level; } ;
typedef  TYPE_1__ cpuctl_cpuid_count_args_t ;
struct TYPE_6__ {int /*<<< orphan*/  data; int /*<<< orphan*/  level; } ;
typedef  TYPE_2__ cpuctl_cpuid_args_t ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int cpuctl_do_cpuid_count (int,TYPE_1__*,struct thread*) ; 

__attribute__((used)) static int
cpuctl_do_cpuid(int cpu, cpuctl_cpuid_args_t *data, struct thread *td)
{
	cpuctl_cpuid_count_args_t cdata;
	int error;

	cdata.level = data->level;
	/* Override the level type. */
	cdata.level_type = 0;
	error = cpuctl_do_cpuid_count(cpu, &cdata, td);
	bcopy(cdata.data, data->data, sizeof(data->data)); /* Ignore error */
	return (error);
}