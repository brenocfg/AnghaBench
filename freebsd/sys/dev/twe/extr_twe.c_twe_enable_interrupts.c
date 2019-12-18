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
struct twe_softc {int /*<<< orphan*/  twe_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  TWE_CONTROL (struct twe_softc*,int) ; 
 int TWE_CONTROL_CLEAR_ATTENTION_INTERRUPT ; 
 int TWE_CONTROL_ENABLE_INTERRUPTS ; 
 int TWE_CONTROL_UNMASK_RESPONSE_INTERRUPT ; 
 int /*<<< orphan*/  TWE_STATE_INTEN ; 

void
twe_enable_interrupts(struct twe_softc *sc)
{
    sc->twe_state |= TWE_STATE_INTEN;
    TWE_CONTROL(sc, 
	       TWE_CONTROL_CLEAR_ATTENTION_INTERRUPT |
	       TWE_CONTROL_UNMASK_RESPONSE_INTERRUPT |
	       TWE_CONTROL_ENABLE_INTERRUPTS);
}