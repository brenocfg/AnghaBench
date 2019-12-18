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
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  atkbdc_softc_t ;

/* Variables and functions */
 int atkbdc_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bushandle (struct resource*) ; 
 int /*<<< orphan*/  rman_get_bustag (struct resource*) ; 

int
atkbdc_attach_unit(int unit, atkbdc_softc_t *sc, struct resource *port0,
		   struct resource *port1)
{
	return atkbdc_setup(sc, rman_get_bustag(port0),
			    rman_get_bushandle(port0),
			    rman_get_bushandle(port1));
}