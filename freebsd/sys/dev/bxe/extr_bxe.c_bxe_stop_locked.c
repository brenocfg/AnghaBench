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
 int /*<<< orphan*/  BXE_CORE_LOCK_ASSERT (struct bxe_softc*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UNLOAD_NORMAL ; 
 int bxe_nic_unload (struct bxe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bxe_stop_locked(struct bxe_softc *sc)
{
    BXE_CORE_LOCK_ASSERT(sc);
    return (bxe_nic_unload(sc, UNLOAD_NORMAL, TRUE));
}