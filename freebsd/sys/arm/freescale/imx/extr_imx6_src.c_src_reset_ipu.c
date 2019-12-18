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

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int RD4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SRC_SCR ; 
 int SW_IPU1_RST ; 
 int /*<<< orphan*/  WR4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * src_sc ; 

int
src_reset_ipu(void)
{
	uint32_t reg;
	int timeout = 10000;

	if (src_sc == NULL)
		return (-1);

	reg = RD4(src_sc, SRC_SCR);
	reg |= SW_IPU1_RST;
	WR4(src_sc, SRC_SCR, reg);

	while (timeout-- > 0) {
		reg = RD4(src_sc, SRC_SCR);
		if (reg & SW_IPU1_RST)
			DELAY(1);
		else
			break;
	}

	if (timeout < 0)
		return (-1);
	else
		return (0);
}