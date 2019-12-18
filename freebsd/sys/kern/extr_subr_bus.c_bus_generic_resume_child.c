#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* device_t ;
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_RESUME (TYPE_1__*) ; 
 int /*<<< orphan*/  DF_SUSPENDED ; 

int
bus_generic_resume_child(device_t dev, device_t child)
{

	DEVICE_RESUME(child);
	child->flags &= ~DF_SUSPENDED;

	return (0);
}