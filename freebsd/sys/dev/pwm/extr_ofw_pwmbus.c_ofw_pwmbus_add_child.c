#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_2__ {int obd_node; } ;
struct ofw_pwmbus_ivars {TYPE_1__ devinfo; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/ * device_add_child_ordered (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ *,struct ofw_pwmbus_ivars*) ; 
 int /*<<< orphan*/  free (struct ofw_pwmbus_ivars*,int /*<<< orphan*/ ) ; 
 struct ofw_pwmbus_ivars* malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static device_t
ofw_pwmbus_add_child(device_t dev, u_int order, const char *name, int unit)
{
	device_t child;
	struct ofw_pwmbus_ivars *ivars;

	if ((ivars = malloc(sizeof(struct ofw_pwmbus_ivars), M_DEVBUF,
	    M_NOWAIT | M_ZERO)) == NULL) {
		return (NULL);
	}

	if ((child = device_add_child_ordered(dev, order, name, unit)) == NULL) {
		free(ivars, M_DEVBUF);
		return (NULL);
	}

	ivars->devinfo.obd_node = -1;
	device_set_ivars(child, ivars);

	return (child);
}