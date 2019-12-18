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
 int /*<<< orphan*/  TWE_IO_LOCK (struct twe_softc*) ; 
 int /*<<< orphan*/  TWE_IO_UNLOCK (struct twe_softc*) ; 
 int /*<<< orphan*/  twe_intr (struct twe_softc*) ; 

__attribute__((used)) static void
twe_pci_intr(void *arg)
{
    struct twe_softc *sc = arg;

    TWE_IO_LOCK(sc);
    twe_intr(sc);
    TWE_IO_UNLOCK(sc);
}