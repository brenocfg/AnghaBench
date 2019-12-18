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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int bcma_add_children (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_delete_children (int /*<<< orphan*/ ) ; 

int
bcma_attach(device_t dev)
{
	int error;

	/* Enumerate children */
	if ((error = bcma_add_children(dev))) {
		device_delete_children(dev);
		return (error);
	}

	return (0);
}