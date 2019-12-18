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
typedef  int /*<<< orphan*/  e6000sw_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  PORT_CONTROL1 ; 
 int PORT_CONTROL1_FID_MASK ; 
 int PORT_MASK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PORT_VLAN_MAP ; 
 int PORT_VLAN_MAP_FID ; 
 int PORT_VLAN_MAP_FID_MASK ; 
 int /*<<< orphan*/  REG_PORT (int /*<<< orphan*/ *,int) ; 
 int e6000sw_readreg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e6000sw_writereg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static __inline void
e6000sw_port_vlan_assign(e6000sw_softc_t *sc, int port, uint32_t fid,
    uint32_t members)
{
	uint32_t reg;

	reg = e6000sw_readreg(sc, REG_PORT(sc, port), PORT_VLAN_MAP);
	reg &= ~(PORT_MASK(sc) | PORT_VLAN_MAP_FID_MASK);
	reg |= members & PORT_MASK(sc) & ~(1 << port);
	reg |= (fid << PORT_VLAN_MAP_FID) & PORT_VLAN_MAP_FID_MASK;
	e6000sw_writereg(sc, REG_PORT(sc, port), PORT_VLAN_MAP, reg);
	reg = e6000sw_readreg(sc, REG_PORT(sc, port), PORT_CONTROL1);
	reg &= ~PORT_CONTROL1_FID_MASK;
	reg |= (fid >> 4) & PORT_CONTROL1_FID_MASK;
	e6000sw_writereg(sc, REG_PORT(sc, port), PORT_CONTROL1, reg);
}