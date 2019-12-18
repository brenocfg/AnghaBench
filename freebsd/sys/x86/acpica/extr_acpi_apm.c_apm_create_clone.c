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
struct cdev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  si_note; } ;
struct apm_clone_data {int flags; TYPE_1__ sel_read; int /*<<< orphan*/  notify_status; struct acpi_softc* acpi_sc; struct cdev* cdev; } ;
struct acpi_softc {int /*<<< orphan*/  apm_cdevs; } ;

/* Variables and functions */
 int ACPI_EVF_DEVD ; 
 int ACPI_EVF_NONE ; 
 int ACPI_EVF_WRITE ; 
 int /*<<< orphan*/  ACPI_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  APM_EV_NONE ; 
 int /*<<< orphan*/  M_APMDEV ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct apm_clone_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi ; 
 int /*<<< orphan*/  acpi_mutex ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  devtoname (struct cdev*) ; 
 int /*<<< orphan*/  entries ; 
 int /*<<< orphan*/  knlist_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct apm_clone_data* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct apm_clone_data *
apm_create_clone(struct cdev *dev, struct acpi_softc *acpi_sc)
{
	struct apm_clone_data *clone;

	clone = malloc(sizeof(*clone), M_APMDEV, M_WAITOK);
	clone->cdev = dev;
	clone->acpi_sc = acpi_sc;
	clone->notify_status = APM_EV_NONE;
	bzero(&clone->sel_read, sizeof(clone->sel_read));
	knlist_init_mtx(&clone->sel_read.si_note, &acpi_mutex);

	/*
	 * The acpi device is always managed by devd(8) and is considered
	 * writable (i.e., ack is required to allow suspend to proceed.)
	 */
	if (strcmp("acpi", devtoname(dev)) == 0)
		clone->flags = ACPI_EVF_DEVD | ACPI_EVF_WRITE;
	else
		clone->flags = ACPI_EVF_NONE;

	ACPI_LOCK(acpi);
	STAILQ_INSERT_TAIL(&acpi_sc->apm_cdevs, clone, entries);
	ACPI_UNLOCK(acpi);
	return (clone);
}