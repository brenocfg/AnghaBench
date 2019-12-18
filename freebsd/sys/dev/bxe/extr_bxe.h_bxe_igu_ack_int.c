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
typedef  scalar_t__ uint16_t ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 scalar_t__ BAR_IGU_INTMEM ; 
 int /*<<< orphan*/  BLOGD (struct bxe_softc*,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  DBG_INTR ; 
 int IGU_REG_SISR_MDPC_WMASK_LSB_UPPER ; 
 scalar_t__ REG_RD (struct bxe_softc*,scalar_t__) ; 
 int /*<<< orphan*/  mb () ; 

__attribute__((used)) static inline uint16_t
bxe_igu_ack_int(struct bxe_softc *sc)
{
    uint32_t igu_addr = (BAR_IGU_INTMEM + IGU_REG_SISR_MDPC_WMASK_LSB_UPPER*8);
    uint32_t result = REG_RD(sc, igu_addr);

    BLOGD(sc, DBG_INTR, "read 0x%08x from IGU addr 0x%x\n",
          result, igu_addr);

    mb();
    return (result);
}