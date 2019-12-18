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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  GPIOBUS_PIN_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int GPIOTHS_DHT_TIMEOUT ; 

__attribute__((used)) static int
gpioths_dht_timeuntil(device_t bus, device_t dev, uint32_t lev, uint32_t *time)
{
	uint32_t	cur_level;
	int		i;

	for (i = 0; i < GPIOTHS_DHT_TIMEOUT; i++) {
		GPIOBUS_PIN_GET(bus, dev, 0, &cur_level);
		if (cur_level == lev) {
			if (time != NULL)
				*time = i;
			return (0);
		}
		DELAY(1);
	}

	/* Timeout */
	return (ETIMEDOUT);
}