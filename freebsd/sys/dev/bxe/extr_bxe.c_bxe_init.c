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
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BXE_CORE_LOCK (struct bxe_softc*) ; 
 int /*<<< orphan*/  BXE_CORE_UNLOCK (struct bxe_softc*) ; 
 int /*<<< orphan*/  bxe_init_locked (struct bxe_softc*) ; 

__attribute__((used)) static void
bxe_init(void *xsc)
{
    struct bxe_softc *sc = (struct bxe_softc *)xsc;

    BXE_CORE_LOCK(sc);
    bxe_init_locked(sc);
    BXE_CORE_UNLOCK(sc);
}