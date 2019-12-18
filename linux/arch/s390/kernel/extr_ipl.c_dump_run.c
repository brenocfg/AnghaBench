#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct shutdown_trigger {int dummy; } ;

/* Variables and functions */
 scalar_t__ DUMP_TYPE_NONE ; 
 int /*<<< orphan*/  __dump_run ; 
 scalar_t__ dump_type ; 
 int /*<<< orphan*/  smp_call_ipl_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_send_stop () ; 

__attribute__((used)) static void dump_run(struct shutdown_trigger *trigger)
{
	if (dump_type == DUMP_TYPE_NONE)
		return;
	smp_send_stop();
	smp_call_ipl_cpu(__dump_run, NULL);
}