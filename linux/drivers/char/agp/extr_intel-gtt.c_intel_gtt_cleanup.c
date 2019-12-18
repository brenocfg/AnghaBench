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
struct TYPE_4__ {int /*<<< orphan*/  registers; int /*<<< orphan*/  gtt; TYPE_1__* driver; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* cleanup ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  intel_gtt_teardown_scratch_page () ; 
 TYPE_2__ intel_private ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static void intel_gtt_cleanup(void)
{
	intel_private.driver->cleanup();

	iounmap(intel_private.gtt);
	iounmap(intel_private.registers);

	intel_gtt_teardown_scratch_page();
}