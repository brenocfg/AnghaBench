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
typedef  int /*<<< orphan*/  grant_ref_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int gnttab_grant_foreign_access (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xenbus_dev_fatal (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  xenbus_get_otherend_id (int /*<<< orphan*/ ) ; 

int
xenbus_grant_ring(device_t dev, unsigned long ring_mfn, grant_ref_t *refp)
{
	int error;

	error = gnttab_grant_foreign_access(
		xenbus_get_otherend_id(dev), ring_mfn, 0, refp);
	if (error) {
		xenbus_dev_fatal(dev, error, "granting access to ring page");
		return (error);
	}

	return (0);
}