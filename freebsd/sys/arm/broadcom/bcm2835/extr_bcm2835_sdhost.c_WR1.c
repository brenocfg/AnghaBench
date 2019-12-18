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
typedef  int uint32_t ;
struct bcm_sdhost_softc {int dummy; } ;
typedef  int bus_size_t ;

/* Variables and functions */
 int RD4 (struct bcm_sdhost_softc*,int) ; 
 int /*<<< orphan*/  WR4 (struct bcm_sdhost_softc*,int,int) ; 

__attribute__((used)) static inline void
WR1(struct bcm_sdhost_softc *sc, bus_size_t off, uint8_t val)
{
	uint32_t val32;

	val32 = RD4(sc, off & ~3);
	val32 &= ~(0xff << (off & 3)*8);
	val32 |= (val << (off & 3)*8);
	WR4(sc, off & ~3, val32);
}