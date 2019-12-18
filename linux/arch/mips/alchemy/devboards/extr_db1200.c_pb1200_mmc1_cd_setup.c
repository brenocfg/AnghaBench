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

/* Variables and functions */
 int BCSR_INT_SD1INSERT ; 
 int /*<<< orphan*/  BCSR_SIGSTAT ; 
 int /*<<< orphan*/  PB1200_SD1_EJECT_INT ; 
 int /*<<< orphan*/  PB1200_SD1_INSERT_INT ; 
 int bcsr_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  pb1200_mmc1_cd ; 
 int /*<<< orphan*/  pb1200_mmc1_cdfn ; 
 int request_threaded_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,void*) ; 

__attribute__((used)) static int pb1200_mmc1_cd_setup(void *mmc_host, int en)
{
	int ret;

	if (en) {
		ret = request_threaded_irq(PB1200_SD1_INSERT_INT, pb1200_mmc1_cd,
				pb1200_mmc1_cdfn, 0, "sd1_insert", mmc_host);
		if (ret)
			goto out;

		ret = request_threaded_irq(PB1200_SD1_EJECT_INT, pb1200_mmc1_cd,
				pb1200_mmc1_cdfn, 0, "sd1_eject", mmc_host);
		if (ret) {
			free_irq(PB1200_SD1_INSERT_INT, mmc_host);
			goto out;
		}

		if (bcsr_read(BCSR_SIGSTAT) & BCSR_INT_SD1INSERT)
			enable_irq(PB1200_SD1_EJECT_INT);
		else
			enable_irq(PB1200_SD1_INSERT_INT);

	} else {
		free_irq(PB1200_SD1_INSERT_INT, mmc_host);
		free_irq(PB1200_SD1_EJECT_INT, mmc_host);
	}
	ret = 0;
out:
	return ret;
}