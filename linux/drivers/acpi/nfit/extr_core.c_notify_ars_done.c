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
struct acpi_nfit_desc {scalar_t__ scrub_count_state; int /*<<< orphan*/  scrub_count; int /*<<< orphan*/  scrub_flags; int /*<<< orphan*/  init_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARS_BUSY ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_notify_dirent (scalar_t__) ; 

__attribute__((used)) static void notify_ars_done(struct acpi_nfit_desc *acpi_desc)
{
	lockdep_assert_held(&acpi_desc->init_mutex);

	clear_bit(ARS_BUSY, &acpi_desc->scrub_flags);
	acpi_desc->scrub_count++;
	if (acpi_desc->scrub_count_state)
		sysfs_notify_dirent(acpi_desc->scrub_count_state);
}