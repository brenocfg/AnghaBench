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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int P0_PHY_READY ; 
 int PHY0_RESET_N ; 
 int PHY1_RESET_N ; 
 int PHY2_RESET_N ; 
 int PHY3_RESET_N ; 
 int /*<<< orphan*/  SATA_CTL ; 
 int SATA_RST_N ; 
 int /*<<< orphan*/  SATA_STATUS ; 
 int /*<<< orphan*/  nlm_get_sata_regbase (int) ; 
 int nlm_read_sata_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int /*<<< orphan*/  sata_clear_glue_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sata_set_glue_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void nlm_sata_firmware_init(int node)
{
	uint32_t reg_val;
	uint64_t regbase;
	int i;

	pr_info("XLP AHCI Initialization started.\n");
	regbase = nlm_get_sata_regbase(node);

	/* Reset SATA */
	sata_clear_glue_reg(regbase, SATA_CTL, SATA_RST_N);
	/* Reset PHY */
	sata_clear_glue_reg(regbase, SATA_CTL,
			(PHY3_RESET_N | PHY2_RESET_N
			 | PHY1_RESET_N | PHY0_RESET_N));

	/* Set SATA */
	sata_set_glue_reg(regbase, SATA_CTL, SATA_RST_N);
	/* Set PHY */
	sata_set_glue_reg(regbase, SATA_CTL,
			(PHY3_RESET_N | PHY2_RESET_N
			 | PHY1_RESET_N | PHY0_RESET_N));

	pr_debug("Waiting for PHYs to come up.\n");
	i = 0;
	do {
		reg_val = nlm_read_sata_reg(regbase, SATA_STATUS);
		i++;
	} while (((reg_val & 0xF0) != 0xF0) && (i < 10000));

	for (i = 0; i < 4; i++) {
		if (reg_val  & (P0_PHY_READY << i))
			pr_info("PHY%d is up.\n", i);
		else
			pr_info("PHY%d is down.\n", i);
	}

	pr_info("XLP AHCI init done.\n");
}