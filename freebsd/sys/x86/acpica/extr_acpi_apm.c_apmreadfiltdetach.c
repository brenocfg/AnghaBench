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
struct knote {struct apm_clone_data* kn_hook; } ;
struct TYPE_2__ {int /*<<< orphan*/  si_note; } ;
struct apm_clone_data {TYPE_1__ sel_read; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi ; 
 int /*<<< orphan*/  knlist_remove (int /*<<< orphan*/ *,struct knote*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
apmreadfiltdetach(struct knote *kn)
{
	struct	apm_clone_data *clone;

	ACPI_LOCK(acpi);
	clone = kn->kn_hook;
	knlist_remove(&clone->sel_read.si_note, kn, 0);
	ACPI_UNLOCK(acpi);
}