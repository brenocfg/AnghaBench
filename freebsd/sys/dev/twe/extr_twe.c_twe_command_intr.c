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
struct twe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TWE_CONTROL (struct twe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TWE_CONTROL_MASK_COMMAND_INTERRUPT ; 
 int /*<<< orphan*/  debug_called (int) ; 

__attribute__((used)) static void
twe_command_intr(struct twe_softc *sc)
{
    debug_called(4);

    /*
     * We don't use this, rather we try to submit commands when we receive
     * them, and when other commands have completed.  Mask it so we don't get
     * another one.
     */
    TWE_CONTROL(sc, TWE_CONTROL_MASK_COMMAND_INTERRUPT);
}