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
 int /*<<< orphan*/  TWE_CONTROL_CLEAR_HOST_INTERRUPT ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  twe_printf (struct twe_softc*,char*) ; 

__attribute__((used)) static void
twe_host_intr(struct twe_softc *sc)
{
    debug_called(4);

    twe_printf(sc, "host interrupt\n");
    TWE_CONTROL(sc, TWE_CONTROL_CLEAR_HOST_INTERRUPT);
}