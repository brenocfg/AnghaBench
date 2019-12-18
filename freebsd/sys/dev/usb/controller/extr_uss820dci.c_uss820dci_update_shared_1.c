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
struct uss820dci_softc {int dummy; } ;

/* Variables and functions */
 int USS820_PEND ; 
 int USS820_READ_1 (struct uss820dci_softc*,int) ; 
 int /*<<< orphan*/  USS820_WRITE_1 (struct uss820dci_softc*,int,int) ; 

__attribute__((used)) static void
uss820dci_update_shared_1(struct uss820dci_softc *sc, uint8_t reg,
    uint8_t keep_mask, uint8_t set_mask)
{
	uint8_t temp;

	USS820_WRITE_1(sc, USS820_PEND, 1);
	temp = USS820_READ_1(sc, reg);
	temp &= (keep_mask);
	temp |= (set_mask);
	USS820_WRITE_1(sc, reg, temp);
	USS820_WRITE_1(sc, USS820_PEND, 0);
}