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
struct ofw_pcib_gen_softc {int /*<<< orphan*/  ops_node; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct ofw_pcib_gen_softc* device_get_softc (int /*<<< orphan*/ ) ; 

phandle_t
ofw_pcib_gen_get_node(device_t bridge, device_t dev)
{
	struct ofw_pcib_gen_softc *sc;

	sc = device_get_softc(bridge);
	return (sc->ops_node);
}