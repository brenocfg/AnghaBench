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
struct TYPE_2__ {int /*<<< orphan*/  si_note; } ;
struct apm_clone_data {scalar_t__ notify_status; TYPE_1__ sel_read; struct acpi_softc* acpi_sc; } ;
struct acpi_softc {scalar_t__ acpi_next_sstate; int /*<<< orphan*/  apm_cdevs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_UNLOCK (int /*<<< orphan*/ ) ; 
 scalar_t__ APM_EV_ACKED ; 
 int /*<<< orphan*/  M_APMDEV ; 
 int /*<<< orphan*/  STAILQ_REMOVE (int /*<<< orphan*/ *,struct apm_clone_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi ; 
 int /*<<< orphan*/  acpi_AckSleepState (struct apm_clone_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apm_clone_data ; 
 int /*<<< orphan*/  entries ; 
 int /*<<< orphan*/  free (struct apm_clone_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  knlist_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seldrain (TYPE_1__*) ; 

__attribute__((used)) static void
apmdtor(void *data)
{
	struct	apm_clone_data *clone;
	struct	acpi_softc *acpi_sc;

	clone = data;
	acpi_sc = clone->acpi_sc;

	/* We are about to lose a reference so check if suspend should occur */
	if (acpi_sc->acpi_next_sstate != 0 &&
	    clone->notify_status != APM_EV_ACKED)
		acpi_AckSleepState(clone, 0);

	/* Remove this clone's data from the list and free it. */
	ACPI_LOCK(acpi);
	STAILQ_REMOVE(&acpi_sc->apm_cdevs, clone, apm_clone_data, entries);
	seldrain(&clone->sel_read);
	knlist_destroy(&clone->sel_read.si_note);
	ACPI_UNLOCK(acpi);
	free(clone, M_APMDEV);
}