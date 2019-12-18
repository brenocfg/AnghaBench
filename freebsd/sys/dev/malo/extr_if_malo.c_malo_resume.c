#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ ic_nrunning; } ;
struct malo_softc {TYPE_1__ malo_ic; } ;

/* Variables and functions */
 int /*<<< orphan*/  malo_init (struct malo_softc*) ; 

void
malo_resume(struct malo_softc *sc)
{

	if (sc->malo_ic.ic_nrunning > 0)
		malo_init(sc);
}