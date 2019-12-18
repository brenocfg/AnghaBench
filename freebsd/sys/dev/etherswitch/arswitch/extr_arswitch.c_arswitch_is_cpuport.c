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
struct arswitch_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR8327 ; 
 int AR8327_PORT_GMAC6 ; 
 scalar_t__ AR8X16_IS_SWITCH (struct arswitch_softc*,int /*<<< orphan*/ ) ; 
 int AR8X16_PORT_CPU ; 

__attribute__((used)) static int
arswitch_is_cpuport(struct arswitch_softc *sc, int port)
{

	return ((port == AR8X16_PORT_CPU) ||
	    ((AR8X16_IS_SWITCH(sc, AR8327) &&
	      port == AR8327_PORT_GMAC6)));
}