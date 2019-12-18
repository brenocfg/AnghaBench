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
struct knote {int /*<<< orphan*/ * kn_fop; struct apm_clone_data* kn_hook; } ;
struct cdev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  si_note; } ;
struct apm_clone_data {TYPE_1__ sel_read; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi ; 
 int /*<<< orphan*/  apm_readfiltops ; 
 int /*<<< orphan*/  devfs_get_cdevpriv (void**) ; 
 int /*<<< orphan*/  knlist_add (int /*<<< orphan*/ *,struct knote*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
apmkqfilter(struct cdev *dev, struct knote *kn)
{
	struct	apm_clone_data *clone;

	devfs_get_cdevpriv((void **)&clone);
	ACPI_LOCK(acpi);
	kn->kn_hook = clone;
	kn->kn_fop = &apm_readfiltops;
	knlist_add(&clone->sel_read.si_note, kn, 0);
	ACPI_UNLOCK(acpi);
	return (0);
}