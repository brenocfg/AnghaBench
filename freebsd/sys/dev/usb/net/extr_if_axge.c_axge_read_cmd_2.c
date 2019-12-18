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
typedef  int /*<<< orphan*/  uint16_t ;
struct axge_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UGETW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  axge_read_mem (struct axge_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int) ; 

__attribute__((used)) static uint16_t
axge_read_cmd_2(struct axge_softc *sc, uint8_t cmd, uint16_t index,
    uint16_t reg)
{
	uint8_t val[2];

	axge_read_mem(sc, cmd, index, reg, &val, 2);
	return (UGETW(val));
}