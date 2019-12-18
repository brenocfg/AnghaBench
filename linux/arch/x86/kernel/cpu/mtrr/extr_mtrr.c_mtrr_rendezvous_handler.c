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
struct set_mtrr_data {unsigned int smp_reg; int /*<<< orphan*/  smp_type; int /*<<< orphan*/  smp_size; int /*<<< orphan*/  smp_base; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_all ) () ;int /*<<< orphan*/  (* set ) (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_online (int /*<<< orphan*/ ) ; 
 scalar_t__ mtrr_aps_delayed_init ; 
 TYPE_1__* mtrr_if ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  stub1 (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 () ; 

__attribute__((used)) static int mtrr_rendezvous_handler(void *info)
{
	struct set_mtrr_data *data = info;

	/*
	 * We use this same function to initialize the mtrrs during boot,
	 * resume, runtime cpu online and on an explicit request to set a
	 * specific MTRR.
	 *
	 * During boot or suspend, the state of the boot cpu's mtrrs has been
	 * saved, and we want to replicate that across all the cpus that come
	 * online (either at the end of boot or resume or during a runtime cpu
	 * online). If we're doing that, @reg is set to something special and on
	 * all the cpu's we do mtrr_if->set_all() (On the logical cpu that
	 * started the boot/resume sequence, this might be a duplicate
	 * set_all()).
	 */
	if (data->smp_reg != ~0U) {
		mtrr_if->set(data->smp_reg, data->smp_base,
			     data->smp_size, data->smp_type);
	} else if (mtrr_aps_delayed_init || !cpu_online(smp_processor_id())) {
		mtrr_if->set_all();
	}
	return 0;
}