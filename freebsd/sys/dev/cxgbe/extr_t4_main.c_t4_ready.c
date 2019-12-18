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
struct adapter {int flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int FW_OK ; 
 struct adapter* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
t4_ready(device_t dev)
{
	struct adapter *sc;

	sc = device_get_softc(dev);
	if (sc->flags & FW_OK)
		return (0);
	return (ENXIO);
}