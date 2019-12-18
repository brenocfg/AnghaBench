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
typedef  int /*<<< orphan*/  uint32_t ;
struct ste_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_SPACE_BARRIER_READ ; 
 int BUS_SPACE_BARRIER_WRITE ; 
 int /*<<< orphan*/  CSR_BARRIER (struct ste_softc*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  CSR_WRITE_1 (struct ste_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STE_PHYCTL ; 
 struct ste_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ste_mii_bitbang_write(device_t dev, uint32_t val)
{
	struct ste_softc *sc;

	sc = device_get_softc(dev);

	CSR_WRITE_1(sc, STE_PHYCTL, val);
	CSR_BARRIER(sc, STE_PHYCTL, 1,
	    BUS_SPACE_BARRIER_READ | BUS_SPACE_BARRIER_WRITE);
}