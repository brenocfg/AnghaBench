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
 int /*<<< orphan*/  WPI_BARRIER_READ_WRITE (struct wpi_softc*) ; 
 int WPI_PRPH_DWORD ; 
 int /*<<< orphan*/  WPI_PRPH_RADDR ; 
 int /*<<< orphan*/  WPI_PRPH_RDATA ; 
 int WPI_READ (struct wpi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPI_WRITE (struct wpi_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static __inline uint32_t
wpi_prph_read(struct wpi_softc *sc, uint32_t addr)
{
	WPI_WRITE(sc, WPI_PRPH_RADDR, WPI_PRPH_DWORD | addr);
	WPI_BARRIER_READ_WRITE(sc);
	return WPI_READ(sc, WPI_PRPH_RDATA);
}