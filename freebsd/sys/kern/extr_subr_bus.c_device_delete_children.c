#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* device_t ;
struct TYPE_7__ {int /*<<< orphan*/  children; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICENAME (TYPE_1__*) ; 
 int /*<<< orphan*/  PDEBUG (char*) ; 
 TYPE_1__* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int device_delete_child (TYPE_1__*,TYPE_1__*) ; 

int
device_delete_children(device_t dev)
{
	device_t child;
	int error;

	PDEBUG(("Deleting all children of %s", DEVICENAME(dev)));

	error = 0;

	while ((child = TAILQ_FIRST(&dev->children)) != NULL) {
		error = device_delete_child(dev, child);
		if (error) {
			PDEBUG(("Failed deleting %s", DEVICENAME(child)));
			break;
		}
	}
	return (error);
}