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
struct sdei_registered_event {int dummy; } ;
struct sdei_crosscall_args {TYPE_1__* event; } ;
struct TYPE_2__ {int /*<<< orphan*/  event_num; int /*<<< orphan*/  private_registered; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 struct sdei_registered_event* per_cpu_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  preemptible () ; 
 int sdei_api_event_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sdei_registered_event*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdei_cross_call_return (struct sdei_crosscall_args*,int) ; 
 int /*<<< orphan*/  sdei_entry_point ; 
 int /*<<< orphan*/  smp_processor_id () ; 

__attribute__((used)) static void _local_event_register(void *data)
{
	int err;
	struct sdei_registered_event *reg;
	struct sdei_crosscall_args *arg = data;

	WARN_ON(preemptible());

	reg = per_cpu_ptr(arg->event->private_registered, smp_processor_id());
	err = sdei_api_event_register(arg->event->event_num, sdei_entry_point,
				      reg, 0, 0);

	sdei_cross_call_return(arg, err);
}