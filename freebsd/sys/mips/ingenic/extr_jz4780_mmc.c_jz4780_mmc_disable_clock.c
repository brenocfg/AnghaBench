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
struct jz4780_mmc_softc {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int JZ_CLK_EN ; 
 int /*<<< orphan*/  JZ_CLOCK_STOP ; 
 int JZ_MMC_READ_4 (struct jz4780_mmc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JZ_MMC_WRITE_4 (struct jz4780_mmc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JZ_MSC_CTRL ; 
 int /*<<< orphan*/  JZ_MSC_STAT ; 

__attribute__((used)) static int
jz4780_mmc_disable_clock(struct jz4780_mmc_softc *sc)
{
	int timeout;

	JZ_MMC_WRITE_4(sc, JZ_MSC_CTRL, JZ_CLOCK_STOP);

	for (timeout = 1000; timeout > 0; timeout--)
		if ((JZ_MMC_READ_4(sc, JZ_MSC_STAT) & JZ_CLK_EN) == 0)
			return (0);
	return (ETIMEDOUT);
}