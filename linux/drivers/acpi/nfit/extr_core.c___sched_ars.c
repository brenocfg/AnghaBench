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
struct acpi_nfit_desc {unsigned int scrub_tmo; int /*<<< orphan*/  dwork; int /*<<< orphan*/  scrub_flags; int /*<<< orphan*/  init_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARS_BUSY ; 
 unsigned int HZ ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfit_wq ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __sched_ars(struct acpi_nfit_desc *acpi_desc, unsigned int tmo)
{
	lockdep_assert_held(&acpi_desc->init_mutex);

	set_bit(ARS_BUSY, &acpi_desc->scrub_flags);
	/* note this should only be set from within the workqueue */
	if (tmo)
		acpi_desc->scrub_tmo = tmo;
	queue_delayed_work(nfit_wq, &acpi_desc->dwork, tmo * HZ);
}