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
struct nge_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_SPACE_BARRIER_READ ; 
 int BUS_SPACE_BARRIER_WRITE ; 
 int /*<<< orphan*/  CSR_BARRIER_4 (struct nge_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct nge_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NGE_MEAR ; 
 struct nge_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nge_mii_bitbang_write(device_t dev, uint32_t val)
{
	struct nge_softc *sc;

	sc = device_get_softc(dev);

	CSR_WRITE_4(sc, NGE_MEAR, val);
	CSR_BARRIER_4(sc, NGE_MEAR,
	    BUS_SPACE_BARRIER_READ | BUS_SPACE_BARRIER_WRITE);
}