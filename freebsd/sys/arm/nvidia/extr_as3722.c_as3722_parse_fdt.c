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
struct as3722_softc {int int_pullup; int i2c_pullup; } ;
typedef  int /*<<< orphan*/  phandle_t ;

/* Variables and functions */
 scalar_t__ OF_hasprop (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
as3722_parse_fdt(struct as3722_softc *sc, phandle_t node)
{

	sc->int_pullup =
	    OF_hasprop(node, "ams,enable-internal-int-pullup") ? 1 : 0;
	sc->i2c_pullup =
	    OF_hasprop(node, "ams,enable-internal-i2c-pullup") ? 1 : 0;
	return 0;
}