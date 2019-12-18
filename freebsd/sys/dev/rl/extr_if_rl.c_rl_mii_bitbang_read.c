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
struct rl_softc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_SPACE_BARRIER_READ ; 
 int BUS_SPACE_BARRIER_WRITE ; 
 int /*<<< orphan*/  CSR_BARRIER (struct rl_softc*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  CSR_READ_1 (struct rl_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RL_MII ; 
 struct rl_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
rl_mii_bitbang_read(device_t dev)
{
	struct rl_softc *sc;
	uint32_t val;

	sc = device_get_softc(dev);

	val = CSR_READ_1(sc, RL_MII);
	CSR_BARRIER(sc, RL_MII, 1,
	    BUS_SPACE_BARRIER_READ | BUS_SPACE_BARRIER_WRITE);

	return (val);
}