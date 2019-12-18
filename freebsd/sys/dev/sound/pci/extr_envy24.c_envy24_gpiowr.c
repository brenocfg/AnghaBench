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
typedef  int u_int32_t ;
struct sc_info {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENVY24_CCI_GPIODAT ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  envy24_wrci (struct sc_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
envy24_gpiowr(struct sc_info *sc, u_int32_t data)
{
#if(0)
	device_printf(sc->dev, "envy24_gpiowr(sc, 0x%02x)\n", data & 0xff);
	return;
#endif
	envy24_wrci(sc, ENVY24_CCI_GPIODAT, data);
	return;
}