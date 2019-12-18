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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct rsu_softc {int dummy; } ;

/* Variables and functions */
 int le32toh (int) ; 
 scalar_t__ rsu_read_region_1 (struct rsu_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static uint32_t
rsu_read_4(struct rsu_softc *sc, uint16_t addr)
{
	uint32_t val;

	if (rsu_read_region_1(sc, addr, (uint8_t *)&val, 4) != 0)
		return (0xffffffff);
	return (le32toh(val));
}