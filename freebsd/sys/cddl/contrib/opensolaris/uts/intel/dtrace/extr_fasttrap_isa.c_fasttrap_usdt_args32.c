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
typedef  scalar_t__ uint32_t ;
struct reg {scalar_t__ r_rsp; } ;
struct TYPE_3__ {int* ftp_argmap; int /*<<< orphan*/  ftp_nargs; } ;
typedef  TYPE_1__ fasttrap_probe_t ;

/* Variables and functions */
 int MIN (int,int /*<<< orphan*/ ) ; 
 scalar_t__ fasttrap_fuword32_noerr (scalar_t__*) ; 

__attribute__((used)) static void
fasttrap_usdt_args32(fasttrap_probe_t *probe, struct reg *rp, int argc,
    uint32_t *argv)
{
	int i, x, cap = MIN(argc, probe->ftp_nargs);
	uint32_t *stack = (uint32_t *)rp->r_rsp;

	for (i = 0; i < cap; i++) {
		x = probe->ftp_argmap[i];

		argv[i] = fasttrap_fuword32_noerr(&stack[x]);
	}

	for (; i < argc; i++) {
		argv[i] = 0;
	}
}