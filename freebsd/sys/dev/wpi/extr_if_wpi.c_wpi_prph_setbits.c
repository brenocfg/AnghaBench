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
struct wpi_softc {int dummy; } ;

/* Variables and functions */
 int wpi_prph_read (struct wpi_softc*,int) ; 
 int /*<<< orphan*/  wpi_prph_write (struct wpi_softc*,int,int) ; 

__attribute__((used)) static __inline void
wpi_prph_setbits(struct wpi_softc *sc, uint32_t addr, uint32_t mask)
{
	wpi_prph_write(sc, addr, wpi_prph_read(sc, addr) | mask);
}