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
struct uv_hub_nmi_s {int /*<<< orphan*/  nmi_lock; int /*<<< orphan*/  in_nmi; } ;
struct TYPE_2__ {int /*<<< orphan*/  queries; } ;

/* Variables and functions */
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  local64_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ raw_spin_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  this_cpu_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 
 TYPE_1__ uv_cpu_nmi ; 
 int /*<<< orphan*/  uv_in_nmi ; 
 int /*<<< orphan*/  uv_nmi_count ; 
 int /*<<< orphan*/  uv_nmi_misses ; 
 int /*<<< orphan*/  uv_nmi_slave_delay ; 
 int /*<<< orphan*/  uv_set_in_nmi (int,struct uv_hub_nmi_s*) ; 
 int uv_test_nmi (struct uv_hub_nmi_s*) ; 

__attribute__((used)) static int uv_check_nmi(struct uv_hub_nmi_s *hub_nmi)
{
	int cpu = smp_processor_id();
	int nmi = 0;
	int nmi_detected = 0;

	local64_inc(&uv_nmi_count);
	this_cpu_inc(uv_cpu_nmi.queries);

	do {
		nmi = atomic_read(&hub_nmi->in_nmi);
		if (nmi)
			break;

		if (raw_spin_trylock(&hub_nmi->nmi_lock)) {
			nmi_detected = uv_test_nmi(hub_nmi);

			/* Check flag for UV external NMI */
			if (nmi_detected > 0) {
				uv_set_in_nmi(cpu, hub_nmi);
				nmi = 1;
				break;
			}

			/* A non-PCH node in a hubless system waits for NMI */
			else if (nmi_detected < 0)
				goto slave_wait;

			/* MMR/PCH NMI flag is clear */
			raw_spin_unlock(&hub_nmi->nmi_lock);

		} else {

			/* Wait a moment for the HUB NMI locker to set flag */
slave_wait:		cpu_relax();
			udelay(uv_nmi_slave_delay);

			/* Re-check hub in_nmi flag */
			nmi = atomic_read(&hub_nmi->in_nmi);
			if (nmi)
				break;
		}

		/*
		 * Check if this BMC missed setting the MMR NMI flag (or)
		 * UV hubless system where only PCH owner can check flag
		 */
		if (!nmi) {
			nmi = atomic_read(&uv_in_nmi);
			if (nmi)
				uv_set_in_nmi(cpu, hub_nmi);
		}

		/* If we're holding the hub lock, release it now */
		if (nmi_detected < 0)
			raw_spin_unlock(&hub_nmi->nmi_lock);

	} while (0);

	if (!nmi)
		local64_inc(&uv_nmi_misses);

	return nmi;
}