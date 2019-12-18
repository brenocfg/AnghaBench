#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* ops; int /*<<< orphan*/  mtx; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* early_init ) (TYPE_3__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MTX_SPIN ; 
 TYPE_3__ main_cons ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 scalar_t__ xen_get_console_evtchn () ; 
 TYPE_1__ xencons_hypervisor_ops ; 
 TYPE_1__ xencons_ring_ops ; 

__attribute__((used)) static void
xencons_early_init(void)
{

	mtx_init(&main_cons.mtx, "XCONS LOCK", NULL, MTX_SPIN);

	if (xen_get_console_evtchn() == 0)
		main_cons.ops = &xencons_hypervisor_ops;
	else
		main_cons.ops = &xencons_ring_ops;

	main_cons.ops->early_init(&main_cons);
}