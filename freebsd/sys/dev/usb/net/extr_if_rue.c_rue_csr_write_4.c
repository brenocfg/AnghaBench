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
typedef  int /*<<< orphan*/  uint32_t ;
struct rue_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  USETDW (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int rue_write_mem (struct rue_softc*,int,int /*<<< orphan*/ **,int) ; 

__attribute__((used)) static int
rue_csr_write_4(struct rue_softc *sc, int reg, uint32_t val)
{
	uint8_t temp[4];

	USETDW(temp, val);
	return (rue_write_mem(sc, reg, &temp, 4));
}