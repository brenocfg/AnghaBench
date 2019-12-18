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
 int DC_RL0_CH_5 ; 
 int IPU_READ4 (struct ipu_softc*,int) ; 
 int /*<<< orphan*/  IPU_WRITE4 (struct ipu_softc*,int,int) ; 

__attribute__((used)) static void
ipu_dc_link_event(struct ipu_softc *sc, int event, int addr, int priority)
{
	uint32_t reg;
	int offset;
	int shift;

	if (event % 2)
		shift = 16;
	else
		shift = 0;

	offset = DC_RL0_CH_5 + (event / 2) * sizeof(uint32_t);

	reg = IPU_READ4(sc, offset);
	reg &= ~(0xFFFF << shift);
	reg |= ((addr << 8) | priority) << shift;
	IPU_WRITE4(sc, offset, reg);
}