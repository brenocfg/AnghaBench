#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
typedef  TYPE_3__* sc_p ;
typedef  int /*<<< orphan*/  driver_intr_t ;
typedef  int /*<<< orphan*/  driver_filter_t ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  devclass_t ;
struct TYPE_5__ {void* arg; int /*<<< orphan*/ * intr; } ;
struct TYPE_4__ {void* arg; int /*<<< orphan*/ * intr; } ;
struct TYPE_6__ {TYPE_2__ pcm_intr; TYPE_1__ midi_intr; } ;

/* Variables and functions */
 int EINVAL ; 
 int bus_generic_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct resource*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,void**) ; 
 int /*<<< orphan*/  devclass_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_devclass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
gusc_setup_intr(device_t dev, device_t child, struct resource *irq, int flags,
		driver_filter_t *filter,
		driver_intr_t *intr, void *arg, void **cookiep)
{
	sc_p scp = (sc_p)device_get_softc(dev);
	devclass_t devclass;

	if (filter != NULL) {
		printf("gusc.c: we cannot use a filter here\n");
		return (EINVAL);
	}
	devclass = device_get_devclass(child);
	if (strcmp(devclass_get_name(devclass), "midi") == 0) {
		scp->midi_intr.intr = intr;
		scp->midi_intr.arg = arg;
		return 0;
	} else if (strcmp(devclass_get_name(devclass), "pcm") == 0) {
		scp->pcm_intr.intr = intr;
		scp->pcm_intr.arg = arg;
		return 0;
	}
	return bus_generic_setup_intr(dev, child, irq, flags,
				filter,
				intr, arg, cookiep);
}