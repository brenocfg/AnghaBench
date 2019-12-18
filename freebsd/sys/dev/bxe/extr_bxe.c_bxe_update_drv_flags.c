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
typedef  scalar_t__ uint32_t ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGD (struct bxe_softc*,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  DBG_LOAD ; 
 int /*<<< orphan*/  HW_LOCK_RESOURCE_DRV_FLAGS ; 
 int /*<<< orphan*/  RESET_FLAGS (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SET_FLAGS (scalar_t__,scalar_t__) ; 
 scalar_t__ SHMEM2_HAS (struct bxe_softc*,scalar_t__) ; 
 scalar_t__ SHMEM2_RD (struct bxe_softc*,scalar_t__) ; 
 int /*<<< orphan*/  SHMEM2_WR (struct bxe_softc*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  bxe_acquire_hw_lock (struct bxe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bxe_release_hw_lock (struct bxe_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bxe_update_drv_flags(struct bxe_softc *sc,
                     uint32_t         flags,
                     uint32_t         set)
{
    uint32_t drv_flags;

    if (SHMEM2_HAS(sc, drv_flags)) {
        bxe_acquire_hw_lock(sc, HW_LOCK_RESOURCE_DRV_FLAGS);
        drv_flags = SHMEM2_RD(sc, drv_flags);

        if (set) {
            SET_FLAGS(drv_flags, flags);
        } else {
            RESET_FLAGS(drv_flags, flags);
        }

        SHMEM2_WR(sc, drv_flags, drv_flags);
        BLOGD(sc, DBG_LOAD, "drv_flags 0x%08x\n", drv_flags);

        bxe_release_hw_lock(sc, HW_LOCK_RESOURCE_DRV_FLAGS);
    }
}