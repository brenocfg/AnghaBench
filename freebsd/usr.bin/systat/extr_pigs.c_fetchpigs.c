#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct p_times {int dummy; } ;
struct kinfo_proc {float ki_swtime; int ki_flag; scalar_t__ ki_pctcpu; } ;
struct TYPE_4__ {float pt_pctcpu; struct kinfo_proc* pt_kp; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_PROC_ALL ; 
 int P_INMEM ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 double exp (float) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 double fscale ; 
 int /*<<< orphan*/  kd ; 
 int /*<<< orphan*/  kvm_geterr (int /*<<< orphan*/ ) ; 
 struct kinfo_proc* kvm_getprocs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 float lccpu ; 
 TYPE_1__* malloc (int) ; 
 int nproc ; 
 TYPE_1__* pt ; 

void
fetchpigs(void)
{
	int i;
	float ftime;
	float *pctp;
	struct kinfo_proc *kpp;
	static int lastnproc = 0;

	if ((kpp = kvm_getprocs(kd, KERN_PROC_ALL, 0, &nproc)) == NULL) {
		error("%s", kvm_geterr(kd));
		if (pt)
			free(pt);
		return;
	}
	if (nproc > lastnproc) {
		free(pt);
		if ((pt =
		    malloc(nproc * sizeof(struct p_times))) == NULL) {
			error("Out of memory");
			die(0);
		}
	}
	lastnproc = nproc;
	/*
	 * calculate %cpu for each proc
	 */
	for (i = 0; i < nproc; i++) {
		pt[i].pt_kp = &kpp[i];
		pctp = &pt[i].pt_pctcpu;
		ftime = kpp[i].ki_swtime;
		if (ftime == 0 || (kpp[i].ki_flag & P_INMEM) == 0)
			*pctp = 0;
		else
			*pctp = ((double) kpp[i].ki_pctcpu /
					fscale) / (1.0 - exp(ftime * lccpu));
	}
}