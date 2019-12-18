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
typedef  int /*<<< orphan*/  u_int ;
struct smbus_ivar {int dummy; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/ * device_add_child_ordered (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ *,struct smbus_ivar*) ; 
 struct smbus_ivar* malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static device_t
smbus_add_child(device_t dev, u_int order, const char *name, int unit)
{
	struct smbus_ivar *devi;
	device_t child;

	child = device_add_child_ordered(dev, order, name, unit);
	if (child == NULL)
		return (child);
	devi = malloc(sizeof(struct smbus_ivar), M_DEVBUF, M_NOWAIT | M_ZERO);
	if (devi == NULL) {
		device_delete_child(dev, child);
		return (NULL);
	}
	device_set_ivars(child, devi);
	return (child);
}