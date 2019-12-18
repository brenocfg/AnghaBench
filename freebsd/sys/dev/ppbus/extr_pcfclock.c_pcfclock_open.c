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
struct thread {int dummy; } ;
struct pcfclock_data {int /*<<< orphan*/  dev; } ;
struct cdev {struct pcfclock_data* si_drv1; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  PPB_DONTWAIT ; 
 int /*<<< orphan*/  PPB_WAIT ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_lock (int /*<<< orphan*/ ) ; 
 int ppb_request_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pcfclock_open(struct cdev *dev, int flag, int fms, struct thread *td)
{
	struct pcfclock_data *sc = dev->si_drv1;
	device_t pcfclockdev;
	device_t ppbus;
	int res;

	if (!sc)
		return (ENXIO);
	pcfclockdev = sc->dev;
	ppbus = device_get_parent(pcfclockdev);

	ppb_lock(ppbus);
	res = ppb_request_bus(ppbus, pcfclockdev,
	    (flag & O_NONBLOCK) ? PPB_DONTWAIT : PPB_WAIT);
	ppb_unlock(ppbus);
	return (res);
}