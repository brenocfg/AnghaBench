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
struct ukswitch_softc {int /*<<< orphan*/  info; } ;
typedef  int /*<<< orphan*/  etherswitch_info_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct ukswitch_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static etherswitch_info_t *
ukswitch_getinfo(device_t dev)
{
	struct ukswitch_softc *sc = device_get_softc(dev);
	
	return (&sc->info);
}