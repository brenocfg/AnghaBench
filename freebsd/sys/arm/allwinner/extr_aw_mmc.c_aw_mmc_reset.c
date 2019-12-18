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
struct aw_mmc_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AW_MMC_GCTL ; 
 int AW_MMC_GCTL_RESET ; 
 int AW_MMC_READ_4 (struct aw_mmc_softc*,int /*<<< orphan*/ ) ; 
 int AW_MMC_RESET_RETRY ; 
 int /*<<< orphan*/  AW_MMC_WRITE_4 (struct aw_mmc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int ETIMEDOUT ; 

__attribute__((used)) static int
aw_mmc_reset(struct aw_mmc_softc *sc)
{
	uint32_t reg;
	int timeout;

	reg = AW_MMC_READ_4(sc, AW_MMC_GCTL);
	reg |= AW_MMC_GCTL_RESET;
	AW_MMC_WRITE_4(sc, AW_MMC_GCTL, reg);
	timeout = AW_MMC_RESET_RETRY;
	while (--timeout > 0) {
		if ((AW_MMC_READ_4(sc, AW_MMC_GCTL) & AW_MMC_GCTL_RESET) == 0)
			break;
		DELAY(100);
	}
	if (timeout == 0)
		return (ETIMEDOUT);

	return (0);
}