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
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ device_delete_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*) ; 
 int device_probe_and_attach (int /*<<< orphan*/ *) ; 

int
bhndb_attach_bridge(device_t parent, device_t *bhndb, int unit)
{
	int error;

	*bhndb = device_add_child(parent, "bhndb", unit);
	if (*bhndb == NULL)
		return (ENXIO);

	if (!(error = device_probe_and_attach(*bhndb)))
		return (0);

	if ((device_delete_child(parent, *bhndb)))
		device_printf(parent, "failed to detach bhndb child\n");

	return (error);
}