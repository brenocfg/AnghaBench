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
struct devinfo_dev {int /*<<< orphan*/  dd_location; int /*<<< orphan*/  dd_name; } ;
struct asn_oid {int dummy; } ;

/* Variables and functions */
 struct asn_oid OIDX_hrDeviceProcessor_c ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strstr (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
device_get_type(struct devinfo_dev *dev_p, const struct asn_oid **out_type_p)
{

	assert(dev_p != NULL);
	assert(out_type_p != NULL);

	if (dev_p == NULL)
		return;

	if (strncmp(dev_p->dd_name, "cpu", strlen("cpu")) == 0 &&
	    strstr(dev_p->dd_location, ".CPU") != NULL) {
		*out_type_p = &OIDX_hrDeviceProcessor_c;
		return;
	}
}