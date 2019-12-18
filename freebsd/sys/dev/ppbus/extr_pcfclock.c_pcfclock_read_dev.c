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
struct pcfclock_data {int /*<<< orphan*/  dev; } ;
struct cdev {struct pcfclock_data* si_drv1; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  PCFCLOCK_CMD_TIME ; 
 int /*<<< orphan*/  PCFCLOCK_CORRECT_FORMAT (char*) ; 
 int /*<<< orphan*/  PCFCLOCK_CORRECT_SYNC (char*) ; 
 int /*<<< orphan*/  PPB_COMPATIBLE ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 scalar_t__ pcfclock_read_data (struct cdev*,char*,int) ; 
 int /*<<< orphan*/  pcfclock_write_cmd (struct cdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_set_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pcfclock_read_dev(struct cdev *dev, char *buf, int maxretries)
{
	struct pcfclock_data *sc = dev->si_drv1;
	device_t pcfclockdev = sc->dev;
	device_t ppbus = device_get_parent(pcfclockdev);
	int error = 0;

	ppb_set_mode(ppbus, PPB_COMPATIBLE);

	while (--maxretries > 0) {
		pcfclock_write_cmd(dev, PCFCLOCK_CMD_TIME);
		if (pcfclock_read_data(dev, buf, 68))
			continue;

		if (!PCFCLOCK_CORRECT_SYNC(buf))
			continue;

		if (!PCFCLOCK_CORRECT_FORMAT(buf))
			continue;

		break;
	}

	if (!maxretries)
		error = EIO;

	return (error);
}