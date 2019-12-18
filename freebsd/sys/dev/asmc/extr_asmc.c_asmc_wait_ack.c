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
typedef  int uint8_t ;
typedef  int u_int ;
struct asmc_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ASMC_CMDPORT_READ (struct asmc_softc*) ; 
 int ASMC_STATUS_MASK ; 
 int /*<<< orphan*/  DELAY (int) ; 
 struct asmc_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
asmc_wait_ack(device_t dev, uint8_t val, int amount)
{
	struct asmc_softc *sc = device_get_softc(dev);
	u_int i;

	val = val & ASMC_STATUS_MASK;

	for (i = 0; i < amount; i++) {
		if ((ASMC_CMDPORT_READ(sc) & ASMC_STATUS_MASK) == val)
			return (0);
		DELAY(10);
	}

	return (1);
}