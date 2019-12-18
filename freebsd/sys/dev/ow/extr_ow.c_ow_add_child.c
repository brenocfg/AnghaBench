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
struct ow_devinfo {int /*<<< orphan*/  romid; } ;
typedef  int /*<<< orphan*/  romid_t ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  M_OW ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ *,struct ow_devinfo*) ; 
 int /*<<< orphan*/  free (struct ow_devinfo*,int /*<<< orphan*/ ) ; 
 struct ow_devinfo* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ow_add_child(device_t dev, romid_t romid)
{
	struct ow_devinfo *di;
	device_t child;

	di = malloc(sizeof(*di), M_OW, M_WAITOK);
	di->romid = romid;
	child = device_add_child(dev, NULL, -1);
	if (child == NULL) {
		free(di, M_OW);
		return ENOMEM;
	}
	device_set_ivars(child, di);
	return (0);
}