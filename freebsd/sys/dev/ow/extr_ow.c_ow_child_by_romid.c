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
struct ow_devinfo {scalar_t__ romid; } ;
typedef  scalar_t__ romid_t ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_TEMP ; 
 scalar_t__ device_get_children (int /*<<< orphan*/ *,int /*<<< orphan*/ ***,int*) ; 
 struct ow_devinfo* device_get_ivars (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

__attribute__((used)) static device_t
ow_child_by_romid(device_t dev, romid_t romid)
{
	device_t *children, retval, child;
	int nkid, i;
	struct ow_devinfo *di;

	if (device_get_children(dev, &children, &nkid) != 0)
		return (NULL);
	retval = NULL;
	for (i = 0; i < nkid; i++) {
		child = children[i];
		di = device_get_ivars(child);
		if (di->romid == romid) {
			retval = child;
			break;
		}
	}
	free(children, M_TEMP);

	return (retval);
}