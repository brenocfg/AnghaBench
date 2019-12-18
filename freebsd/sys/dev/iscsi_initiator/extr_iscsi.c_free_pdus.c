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
struct isc_softc {int /*<<< orphan*/ * pdu_zone; } ;

/* Variables and functions */
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  uma_zdestroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
free_pdus(struct isc_softc *sc)
{
     debug_called(8);

     if(sc->pdu_zone != NULL) {
	  uma_zdestroy(sc->pdu_zone);
	  sc->pdu_zone = NULL;
     }
}