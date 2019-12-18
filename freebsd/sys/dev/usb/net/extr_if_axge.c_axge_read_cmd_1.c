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
 int /*<<< orphan*/  axge_read_mem (struct axge_softc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static uint8_t
axge_read_cmd_1(struct axge_softc *sc, uint8_t cmd, uint16_t reg)
{
	uint8_t val;

	axge_read_mem(sc, cmd, 1, reg, &val, 1);
	return (val);
}