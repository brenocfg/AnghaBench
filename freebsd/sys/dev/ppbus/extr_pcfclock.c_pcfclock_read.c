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
struct uio {int uio_resid; } ;
struct pcfclock_data {int /*<<< orphan*/  dev; } ;
struct cdev {struct pcfclock_data* si_drv1; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ERANGE ; 
 int /*<<< orphan*/  PCFCLOCK_MAX_RETRIES ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pcfclock_display_data (struct cdev*,char*) ; 
 int pcfclock_read_dev (struct cdev*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiomove (char*,int,struct uio*) ; 

__attribute__((used)) static int
pcfclock_read(struct cdev *dev, struct uio *uio, int ioflag)
{
	struct pcfclock_data *sc = dev->si_drv1;
	device_t ppbus;
	char buf[18];
	int error = 0;

	if (uio->uio_resid < 18)
		return (ERANGE);

	ppbus = device_get_parent(sc->dev);
	ppb_lock(ppbus);
	error = pcfclock_read_dev(dev, buf, PCFCLOCK_MAX_RETRIES);
	ppb_unlock(ppbus);

	if (error) {
		device_printf(sc->dev, "no PCF found\n");
	} else {
		pcfclock_display_data(dev, buf);

		uiomove(buf, 18, uio);
	}

	return (error);
}