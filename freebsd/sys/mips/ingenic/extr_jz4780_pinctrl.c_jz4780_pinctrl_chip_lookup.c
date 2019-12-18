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
struct jz4780_pinctrl_softc {int dummy; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  OF_device_from_xref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static device_t
jz4780_pinctrl_chip_lookup(struct jz4780_pinctrl_softc *sc, phandle_t chipxref)
{
	device_t chipdev;

	chipdev = OF_device_from_xref(chipxref);
	return chipdev;
}