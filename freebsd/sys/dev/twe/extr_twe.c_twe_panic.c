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
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  twe_print_controller (struct twe_softc*) ; 
 int /*<<< orphan*/  twe_reset (struct twe_softc*) ; 

__attribute__((used)) static void
twe_panic(struct twe_softc *sc, char *reason)
{
    twe_print_controller(sc);
#ifdef TWE_DEBUG
    panic(reason);
#else
    twe_reset(sc);
#endif
}