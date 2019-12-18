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
typedef  scalar_t__ uint16_t ;
struct bwi_softc {int dummy; } ;

/* Variables and functions */
 scalar_t__ BWI_SPROM_START ; 
 scalar_t__ CSR_READ_2 (struct bwi_softc*,scalar_t__) ; 

uint16_t
bwi_read_sprom(struct bwi_softc *sc, uint16_t ofs)
{
	return CSR_READ_2(sc, ofs + BWI_SPROM_START);
}