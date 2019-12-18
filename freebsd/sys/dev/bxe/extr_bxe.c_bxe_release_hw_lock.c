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
typedef  int uint32_t ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGE (struct bxe_softc*,char*,int,int,...) ; 
 int HW_LOCK_MAX_RESOURCE_VALUE ; 
 int MISC_REG_DRIVER_CONTROL_1 ; 
 int MISC_REG_DRIVER_CONTROL_7 ; 
 int REG_RD (struct bxe_softc*,int) ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,int,int) ; 
 int SC_FUNC (struct bxe_softc*) ; 

__attribute__((used)) static int
bxe_release_hw_lock(struct bxe_softc *sc,
                    uint32_t         resource)
{
    uint32_t lock_status;
    uint32_t resource_bit = (1 << resource);
    int func = SC_FUNC(sc);
    uint32_t hw_lock_control_reg;

    /* validate the resource is within range */
    if (resource > HW_LOCK_MAX_RESOURCE_VALUE) {
        BLOGE(sc, "(resource 0x%x > HW_LOCK_MAX_RESOURCE_VALUE)"
            " resource_bit 0x%x\n", resource, resource_bit);
        return (-1);
    }

    if (func <= 5) {
        hw_lock_control_reg = (MISC_REG_DRIVER_CONTROL_1 + (func * 8));
    } else {
        hw_lock_control_reg =
                (MISC_REG_DRIVER_CONTROL_7 + ((func - 6) * 8));
    }

    /* validate the resource is currently taken */
    lock_status = REG_RD(sc, hw_lock_control_reg);
    if (!(lock_status & resource_bit)) {
        BLOGE(sc, "resource (0x%x) not in use (status 0x%x bit 0x%x)\n",
              resource, lock_status, resource_bit);
        return (-1);
    }

    REG_WR(sc, hw_lock_control_reg, resource_bit);
    return (0);
}