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
struct syscon {int dummy; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int ENODEV ; 
 int SYSCON_GET_HANDLE (int /*<<< orphan*/ *,struct syscon**) ; 
 int /*<<< orphan*/ * device_get_parent (int /*<<< orphan*/ *) ; 

int
syscon_get_handle_default(device_t dev, struct syscon **syscon)
{
	device_t parent;

	parent = device_get_parent(dev);
	if (parent == NULL)
		return (ENODEV);
	return (SYSCON_GET_HANDLE(parent, syscon));
}