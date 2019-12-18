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
struct sis_softc {scalar_t__ sis_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIS_LOCK_ASSERT (struct sis_softc*) ; 
 scalar_t__ SIS_TYPE_83815 ; 
 int /*<<< orphan*/  sis_rxfilter_ns (struct sis_softc*) ; 
 int /*<<< orphan*/  sis_rxfilter_sis (struct sis_softc*) ; 

__attribute__((used)) static void
sis_rxfilter(struct sis_softc *sc)
{

	SIS_LOCK_ASSERT(sc);

	if (sc->sis_type == SIS_TYPE_83815)
		sis_rxfilter_ns(sc);
	else
		sis_rxfilter_sis(sc);
}