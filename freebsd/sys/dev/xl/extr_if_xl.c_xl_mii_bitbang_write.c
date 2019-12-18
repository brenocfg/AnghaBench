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
struct xl_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_SPACE_BARRIER_READ ; 
 int BUS_SPACE_BARRIER_WRITE ; 
 int /*<<< orphan*/  CSR_BARRIER (struct xl_softc*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct xl_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XL_W4_PHY_MGMT ; 
 struct xl_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xl_mii_bitbang_write(device_t dev, uint32_t val)
{
	struct xl_softc		*sc;

	sc = device_get_softc(dev);

	/* We're already in window 4. */
	CSR_WRITE_2(sc, XL_W4_PHY_MGMT,	val);
	CSR_BARRIER(sc, XL_W4_PHY_MGMT, 2,
	    BUS_SPACE_BARRIER_READ | BUS_SPACE_BARRIER_WRITE);
}