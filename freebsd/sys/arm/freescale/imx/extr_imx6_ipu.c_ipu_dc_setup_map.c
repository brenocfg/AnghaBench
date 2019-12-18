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
struct ipu_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_MAP_CONF_PTR (int) ; 
 int /*<<< orphan*/  DC_MAP_CONF_VAL (int) ; 
 int IPU_READ4 (struct ipu_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPU_WRITE4 (struct ipu_softc*,int /*<<< orphan*/ ,int) ; 
 int MAP_CONF_PTR_MASK ; 

__attribute__((used)) static void
ipu_dc_setup_map(struct ipu_softc *sc, int map,
    int byte, int offset, int mask)
{
	uint32_t reg, shift, ptr;

	ptr = map * 3 + byte;

	reg = IPU_READ4(sc, DC_MAP_CONF_VAL(ptr));
	if (ptr & 1)
		shift = 16;
	else
		shift = 0;
	reg &= ~(0xffff << shift);
	reg |= ((offset << 8) | mask) << shift;
	IPU_WRITE4(sc, DC_MAP_CONF_VAL(ptr), reg);

	reg = IPU_READ4(sc, DC_MAP_CONF_PTR(map));
	if (map & 1)
		shift = 16  + 5 * byte;
	else
		shift = 5 * byte;
	reg &= ~(MAP_CONF_PTR_MASK << shift);
	reg |= (ptr) << shift;
	IPU_WRITE4(sc, DC_MAP_CONF_PTR(map), reg);
}