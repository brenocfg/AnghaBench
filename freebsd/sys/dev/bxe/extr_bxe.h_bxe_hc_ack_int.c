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
 scalar_t__ COMMAND_REG_SIMD_MASK ; 
 scalar_t__ HC_REG_COMMAND_REG ; 
 scalar_t__ REG_RD (struct bxe_softc*,scalar_t__) ; 
 int SC_PORT (struct bxe_softc*) ; 
 int /*<<< orphan*/  mb () ; 

__attribute__((used)) static inline uint16_t
bxe_hc_ack_int(struct bxe_softc *sc)
{
    uint32_t hc_addr = (HC_REG_COMMAND_REG + SC_PORT(sc)*32 +
                        COMMAND_REG_SIMD_MASK);
    uint32_t result = REG_RD(sc, hc_addr);

    mb();
    return (result);
}