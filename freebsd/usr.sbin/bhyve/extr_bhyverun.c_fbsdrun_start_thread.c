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
typedef  int /*<<< orphan*/  tname ;
struct mt_vmm_info {int mt_vcpu; int /*<<< orphan*/  mt_ctx; int /*<<< orphan*/  mt_thr; } ;
struct TYPE_2__ {int /*<<< orphan*/  rip; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAXCOMLEN ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  gdb_cpu_add (int) ; 
 int /*<<< orphan*/  pthread_set_name_np (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  vm_loop (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* vmexit ; 

__attribute__((used)) static void *
fbsdrun_start_thread(void *param)
{
	char tname[MAXCOMLEN + 1];
	struct mt_vmm_info *mtp;
	int vcpu;

	mtp = param;
	vcpu = mtp->mt_vcpu;

	snprintf(tname, sizeof(tname), "vcpu %d", vcpu);
	pthread_set_name_np(mtp->mt_thr, tname);

	gdb_cpu_add(vcpu);

	vm_loop(mtp->mt_ctx, vcpu, vmexit[vcpu].rip);

	/* not reached */
	exit(1);
	return (NULL);
}