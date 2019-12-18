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
struct cas_softc {int dummy; } ;
typedef  int /*<<< orphan*/  bus_addr_t ;

/* Variables and functions */
 int CAS_READ_4 (struct cas_softc*,int /*<<< orphan*/ ) ; 
 int CAS_TRIES ; 
 int /*<<< orphan*/  DELAY (int) ; 

__attribute__((used)) static int
cas_bitwait(struct cas_softc *sc, bus_addr_t r, uint32_t clr, uint32_t set)
{
	int i;
	uint32_t reg;

	for (i = CAS_TRIES; i--; DELAY(100)) {
		reg = CAS_READ_4(sc, r);
		if ((reg & clr) == 0 && (reg & set) == set)
			return (1);
	}
	return (0);
}