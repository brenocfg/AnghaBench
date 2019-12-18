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
typedef  int uint16_t ;
struct ure_softc {int dummy; } ;

/* Variables and functions */
 int URE_BYTE_EN_DWORD ; 
 int /*<<< orphan*/  USETDW (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ure_write_mem (struct ure_softc*,int,int,int /*<<< orphan*/ **,int) ; 

__attribute__((used)) static int
ure_write_4(struct ure_softc *sc, uint16_t reg, uint16_t index, uint32_t val)
{
	uint8_t temp[4];

	USETDW(temp, val);
	return (ure_write_mem(sc, reg, index | URE_BYTE_EN_DWORD, &temp, 4));
}