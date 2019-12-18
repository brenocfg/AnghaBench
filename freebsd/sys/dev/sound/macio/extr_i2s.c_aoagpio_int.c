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
struct aoagpio_softc {int level; int detect_active; scalar_t__ i2s; } ;
typedef  void* device_t ;

/* Variables and functions */
 int GPIO_LEVEL_RO ; 
 struct aoagpio_softc* device_get_softc (void*) ; 
 int /*<<< orphan*/  i2s_cint (scalar_t__) ; 
 int macgpio_read (void*) ; 

__attribute__((used)) static void
aoagpio_int(void *cookie)
{
	device_t 		 self = cookie;
	struct aoagpio_softc	*sc;

	sc = device_get_softc(self);
	
	if (macgpio_read(self) & GPIO_LEVEL_RO)
		sc->level = sc->detect_active;
	else
		sc->level = !(sc->detect_active);

	if (sc->i2s)
		i2s_cint(sc->i2s);
}