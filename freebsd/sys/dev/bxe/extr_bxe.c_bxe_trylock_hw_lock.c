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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGD (struct bxe_softc*,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  BLOGE (struct bxe_softc*,char*,int,int,int,int) ; 
 int /*<<< orphan*/  DBG_LOAD ; 
 int /*<<< orphan*/  FALSE ; 
 int HW_LOCK_MAX_RESOURCE_VALUE ; 
 int MISC_REG_DRIVER_CONTROL_1 ; 
 int MISC_REG_DRIVER_CONTROL_7 ; 
 int REG_RD (struct bxe_softc*,int) ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,int,int) ; 
 int SC_FUNC (struct bxe_softc*) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static uint8_t
bxe_trylock_hw_lock(struct bxe_softc *sc,
                    uint32_t         resource)
{
    uint32_t lock_status;
    uint32_t resource_bit = (1 << resource);
    int func = SC_FUNC(sc);
    uint32_t hw_lock_control_reg;

    BLOGD(sc, DBG_LOAD, "Trying to take a resource lock 0x%x\n", resource);

    /* Validating that the resource is within range */
    if (resource > HW_LOCK_MAX_RESOURCE_VALUE) {
        BLOGD(sc, DBG_LOAD,
              "resource(0x%x) > HW_LOCK_MAX_RESOURCE_VALUE(0x%x)\n",
              resource, HW_LOCK_MAX_RESOURCE_VALUE);
        return (FALSE);
    }

    if (func <= 5) {
        hw_lock_control_reg = (MISC_REG_DRIVER_CONTROL_1 + func*8);
    } else {
        hw_lock_control_reg = (MISC_REG_DRIVER_CONTROL_7 + (func - 6)*8);
    }

    /* try to acquire the lock */
    REG_WR(sc, hw_lock_control_reg + 4, resource_bit);
    lock_status = REG_RD(sc, hw_lock_control_reg);
    if (lock_status & resource_bit) {
        return (TRUE);
    }

    BLOGE(sc, "Failed to get a resource lock 0x%x func %d "
        "lock_status 0x%x resource_bit 0x%x\n", resource, func,
        lock_status, resource_bit);

    return (FALSE);
}