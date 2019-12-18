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
typedef  int /*<<< orphan*/  uint64_t ;
struct thunder_pem_softc {int /*<<< orphan*/  reg_bsh; int /*<<< orphan*/  reg_bst; } ;

/* Variables and functions */
 int BUS_SPACE_BARRIER_READ ; 
 int BUS_SPACE_BARRIER_WRITE ; 
 int /*<<< orphan*/  PEM_CFG_RD ; 
 int /*<<< orphan*/  PEM_CFG_RD_REG_ALIGN (int) ; 
 int /*<<< orphan*/  PEM_CFG_RD_REG_DATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_space_barrier (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  bus_space_read_8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_space_write_8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64_t
thunder_pem_config_reg_read(struct thunder_pem_softc *sc, int reg)
{
	uint64_t data;

	/* Write to ADDR register */
	bus_space_write_8(sc->reg_bst, sc->reg_bsh, PEM_CFG_RD,
	    PEM_CFG_RD_REG_ALIGN(reg));
	bus_space_barrier(sc->reg_bst, sc->reg_bsh, PEM_CFG_RD, 8,
	    BUS_SPACE_BARRIER_READ | BUS_SPACE_BARRIER_WRITE);
	/* Read from DATA register */
	data = PEM_CFG_RD_REG_DATA(bus_space_read_8(sc->reg_bst, sc->reg_bsh,
	    PEM_CFG_RD));

	return (data);
}