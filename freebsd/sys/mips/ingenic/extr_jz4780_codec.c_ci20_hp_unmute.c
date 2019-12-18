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
struct codec_softc {int dummy; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int CI20_HP_PIN ; 
 int CI20_HP_PORT ; 
 int /*<<< orphan*/  GPIO_PIN_OUTPUT ; 
 int GPIO_PIN_SET (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int GPIO_PIN_SETFLAGS (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devclass_find (char*) ; 
 int /*<<< orphan*/ * devclass_get_device (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ci20_hp_unmute(struct codec_softc *sc)
{
	device_t dev;
	int port;
	int err;
	int pin;

	pin = CI20_HP_PIN;
	port = CI20_HP_PORT;

	dev = devclass_get_device(devclass_find("gpio"), port);
	if (dev == NULL)
		return (0);

	err = GPIO_PIN_SETFLAGS(dev, pin, GPIO_PIN_OUTPUT);
	if (err != 0) {
		device_printf(dev, "Cannot configure GPIO pin %d on %s\n",
		    pin, device_get_nameunit(dev));
		return (err);
	}

	err = GPIO_PIN_SET(dev, pin, 0);
	if (err != 0) {
		device_printf(dev, "Cannot configure GPIO pin %d on %s\n",
		    pin, device_get_nameunit(dev));
		return (err);
	}

	return (0);
}