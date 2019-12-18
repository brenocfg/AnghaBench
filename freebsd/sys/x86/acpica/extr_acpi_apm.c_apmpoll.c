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
struct thread {int dummy; } ;
struct cdev {int dummy; } ;
struct apm_clone_data {int /*<<< orphan*/  sel_read; TYPE_1__* acpi_sc; } ;
struct TYPE_2__ {scalar_t__ acpi_next_sstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_UNLOCK (int /*<<< orphan*/ ) ; 
 int POLLIN ; 
 int POLLRDNORM ; 
 int /*<<< orphan*/  acpi ; 
 int /*<<< orphan*/  devfs_get_cdevpriv (void**) ; 
 int /*<<< orphan*/  selrecord (struct thread*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
apmpoll(struct cdev *dev, int events, struct thread *td)
{
	struct	apm_clone_data *clone;
	int revents;

	revents = 0;
	devfs_get_cdevpriv((void **)&clone);
	ACPI_LOCK(acpi);
	if (clone->acpi_sc->acpi_next_sstate)
		revents |= events & (POLLIN | POLLRDNORM);
	else
		selrecord(td, &clone->sel_read);
	ACPI_UNLOCK(acpi);
	return (revents);
}