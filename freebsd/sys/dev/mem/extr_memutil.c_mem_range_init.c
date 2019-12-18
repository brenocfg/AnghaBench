#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* mr_op; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* init ) (TYPE_2__*) ;} ;

/* Variables and functions */
 TYPE_2__ mem_range_softc ; 
 int /*<<< orphan*/  mr_lock ; 
 int /*<<< orphan*/  rw_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

void
mem_range_init(void)
{

	if (mem_range_softc.mr_op == NULL)
		return;
	rw_init(&mr_lock, "memrange");
	mem_range_softc.mr_op->init(&mem_range_softc);
}