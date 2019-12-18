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
struct thread {int dummy; } ;
struct cdev {int dummy; } ;
struct apm_clone_data {int /*<<< orphan*/  flags; } ;
struct acpi_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_EVF_WRITE ; 
 int FWRITE ; 
 struct apm_clone_data* apm_create_clone (struct cdev*,struct acpi_softc*) ; 
 int /*<<< orphan*/  apmdtor ; 
 int /*<<< orphan*/  devclass_find (char*) ; 
 struct acpi_softc* devclass_get_softc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devfs_set_cdevpriv (struct apm_clone_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
apmopen(struct cdev *dev, int flag, int fmt, struct thread *td)
{
	struct	acpi_softc *acpi_sc;
	struct 	apm_clone_data *clone;

	acpi_sc = devclass_get_softc(devclass_find("acpi"), 0);
	clone = apm_create_clone(dev, acpi_sc);
	devfs_set_cdevpriv(clone, apmdtor);

	/* If the device is opened for write, record that. */
	if ((flag & FWRITE) != 0)
		clone->flags |= ACPI_EVF_WRITE;

	return (0);
}