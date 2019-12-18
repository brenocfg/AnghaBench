#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  xstate_bv; } ;
struct TYPE_3__ {TYPE_2__ sx_hd; } ;
struct savefpu_ymm {TYPE_1__ sv_xstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  bzero (TYPE_2__*,int) ; 
 int /*<<< orphan*/  cpu_max_ext_state_size ; 
 void* malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ use_xsave ; 
 int /*<<< orphan*/  xsave_mask ; 

void *
alloc_fpusave(int flags)
{
	void *res;
	struct savefpu_ymm *sf;

	res = malloc(cpu_max_ext_state_size, M_DEVBUF, flags);
	if (use_xsave) {
		sf = (struct savefpu_ymm *)res;
		bzero(&sf->sv_xstate.sx_hd, sizeof(sf->sv_xstate.sx_hd));
		sf->sv_xstate.sx_hd.xstate_bv = xsave_mask;
	}
	return (res);
}