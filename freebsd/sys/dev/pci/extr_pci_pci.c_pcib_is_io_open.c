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
struct pcib_softc {scalar_t__ iobase; scalar_t__ iolimit; } ;

/* Variables and functions */

__attribute__((used)) static int
pcib_is_io_open(struct pcib_softc *sc)
{
	return (sc->iobase > 0 && sc->iobase < sc->iolimit);
}