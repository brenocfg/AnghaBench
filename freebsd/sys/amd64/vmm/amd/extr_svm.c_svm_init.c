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
struct TYPE_2__ {unsigned long gen; scalar_t__ num; } ;

/* Variables and functions */
 int ENXIO ; 
 int MAXCPU ; 
 int /*<<< orphan*/  VMCB_CACHE_DEFAULT ; 
 TYPE_1__* asid ; 
 int check_svm_features () ; 
 scalar_t__ nasid ; 
 int /*<<< orphan*/  smp_rendezvous (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svm_available () ; 
 int /*<<< orphan*/  svm_enable ; 
 int /*<<< orphan*/  svm_msr_init () ; 
 int /*<<< orphan*/  svm_npt_init (int) ; 
 int /*<<< orphan*/  vmcb_clean ; 

__attribute__((used)) static int
svm_init(int ipinum)
{
	int error, cpu;

	if (!svm_available())
		return (ENXIO);

	error = check_svm_features();
	if (error)
		return (error);

	vmcb_clean &= VMCB_CACHE_DEFAULT;

	for (cpu = 0; cpu < MAXCPU; cpu++) {
		/*
		 * Initialize the host ASIDs to their "highest" valid values.
		 *
		 * The next ASID allocation will rollover both 'gen' and 'num'
		 * and start off the sequence at {1,1}.
		 */
		asid[cpu].gen = ~0UL;
		asid[cpu].num = nasid - 1;
	}

	svm_msr_init();
	svm_npt_init(ipinum);

	/* Enable SVM on all CPUs */
	smp_rendezvous(NULL, svm_enable, NULL, NULL);

	return (0);
}