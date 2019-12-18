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
typedef  int uint8_t ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int PCIM_EXP_STA_TRANSACTION_PND ; 
 int /*<<< orphan*/  PCIR_EXPRESS_DEVICE_STA ; 
 int bxe_pcie_capability_read (struct bxe_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static uint8_t
bxe_is_pcie_pending(struct bxe_softc *sc)
{
    return (bxe_pcie_capability_read(sc, PCIR_EXPRESS_DEVICE_STA, 2) &
            PCIM_EXP_STA_TRANSACTION_PND);
}