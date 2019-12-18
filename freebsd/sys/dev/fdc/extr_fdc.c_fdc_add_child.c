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
struct fdc_ivars {int fdunit; int /*<<< orphan*/  fdtype; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/  FDT_NONE ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  device_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ *,struct fdc_ivars*) ; 
 int /*<<< orphan*/  free (struct fdc_ivars*,int /*<<< orphan*/ ) ; 
 struct fdc_ivars* malloc (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ resource_disabled (char const*,int) ; 

device_t
fdc_add_child(device_t dev, const char *name, int unit)
{
	struct fdc_ivars *ivar;
	device_t child;

	ivar = malloc(sizeof *ivar, M_DEVBUF /* XXX */, M_NOWAIT | M_ZERO);
	if (ivar == NULL)
		return (NULL);
	child = device_add_child(dev, name, unit);
	if (child == NULL) {
		free(ivar, M_DEVBUF);
		return (NULL);
	}
	device_set_ivars(child, ivar);
	ivar->fdunit = unit;
	ivar->fdtype = FDT_NONE;
	if (resource_disabled(name, unit))
		device_disable(child);
	return (child);
}