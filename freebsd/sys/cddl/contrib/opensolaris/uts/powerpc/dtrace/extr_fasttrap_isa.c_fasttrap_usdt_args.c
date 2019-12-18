#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct reg {uintptr_t* fixreg; } ;
struct TYPE_3__ {int* ftp_argmap; int /*<<< orphan*/  ftp_nargs; } ;
typedef  TYPE_1__ fasttrap_probe_t ;

/* Variables and functions */
 int MIN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SV_ILP32 ; 
 scalar_t__ SV_PROC_FLAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curproc ; 
 uintptr_t fuword32 (void*) ; 
 uintptr_t fuword64 (void*) ; 

__attribute__((used)) static void
fasttrap_usdt_args(fasttrap_probe_t *probe, struct reg *rp, int argc,
    uintptr_t *argv)
{
	int i, x, cap = MIN(argc, probe->ftp_nargs);

	for (i = 0; i < cap; i++) {
		x = probe->ftp_argmap[i];

		if (x < 8)
			argv[i] = rp->fixreg[x];
		else
			if (SV_PROC_FLAG(curproc, SV_ILP32))
				argv[i] = fuword32((void *)(rp->fixreg[1] + 8 +
				    (x * sizeof(uint32_t))));
			else
				argv[i] = fuword64((void *)(rp->fixreg[1] + 48 +
				    (x * sizeof(uint64_t))));
	}

	for (; i < argc; i++) {
		argv[i] = 0;
	}
}