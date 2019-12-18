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
typedef  scalar_t__ uint32_t ;
struct fsi_master_acf {scalar_t__ cvic; scalar_t__ sram; int /*<<< orphan*/  t_echo_delay; int /*<<< orphan*/  t_send_delay; int /*<<< orphan*/  dev; scalar_t__ is_ast2500; } ;

/* Variables and functions */
 scalar_t__ CF_STARTED ; 
 scalar_t__ ECHO_DLY_REG ; 
 int ENODEV ; 
 scalar_t__ SEND_DLY_REG ; 
 int /*<<< orphan*/  SRAM_SIZE ; 
 int check_firmware_image (struct fsi_master_acf*) ; 
 int copro_enable_sw_irq (struct fsi_master_acf*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ioread8 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite8 (int /*<<< orphan*/ ,scalar_t__) ; 
 int load_copro_firmware (struct fsi_master_acf*) ; 
 int /*<<< orphan*/  memset_io (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  release_copro_gpios (struct fsi_master_acf*) ; 
 int /*<<< orphan*/  reset_cf (struct fsi_master_acf*) ; 
 int /*<<< orphan*/  setup_ast2400_cf_maps (struct fsi_master_acf*) ; 
 int /*<<< orphan*/  setup_ast2400_fw_config (struct fsi_master_acf*) ; 
 int /*<<< orphan*/  setup_ast2500_cf_maps (struct fsi_master_acf*) ; 
 int /*<<< orphan*/  setup_ast2500_fw_config (struct fsi_master_acf*) ; 
 int setup_gpios_for_copro (struct fsi_master_acf*) ; 
 int /*<<< orphan*/  start_cf (struct fsi_master_acf*) ; 

__attribute__((used)) static int fsi_master_acf_setup(struct fsi_master_acf *master)
{
	int timeout, rc;
	uint32_t val;

	/* Make sure the ColdFire is stopped  */
	reset_cf(master);

	/*
	 * Clear SRAM. This needs to happen before we setup the GPIOs
	 * as we might start trying to arbitrate as soon as that happens.
	 */
	memset_io(master->sram, 0, SRAM_SIZE);

	/* Configure GPIOs */
	rc = setup_gpios_for_copro(master);
	if (rc)
		return rc;

	/* Load the firmware into the reserved memory */
	rc = load_copro_firmware(master);
	if (rc)
		return rc;

	/* Read signature and check versions */
	rc = check_firmware_image(master);
	if (rc)
		return rc;

	/* Setup coldfire memory map */
	if (master->is_ast2500) {
		setup_ast2500_cf_maps(master);
		setup_ast2500_fw_config(master);
	} else {
		setup_ast2400_cf_maps(master);
		setup_ast2400_fw_config(master);
	}

	/* Start the ColdFire */
	start_cf(master);

	/* Wait for status register to indicate command completion
	 * which signals the initialization is complete
	 */
	for (timeout = 0; timeout < 10; timeout++) {
		val = ioread8(master->sram + CF_STARTED);
		if (val)
			break;
		msleep(1);
	}
	if (!val) {
		dev_err(master->dev, "Coprocessor startup timeout !\n");
		rc = -ENODEV;
		goto err;
	}

	/* Configure echo & send delay */
	iowrite8(master->t_send_delay, master->sram + SEND_DLY_REG);
	iowrite8(master->t_echo_delay, master->sram + ECHO_DLY_REG);

	/* Enable SW interrupt to copro if any */
	if (master->cvic) {
		rc = copro_enable_sw_irq(master);
		if (rc)
			goto err;
	}
	return 0;
 err:
	/* An error occurred, don't leave the coprocessor running */
	reset_cf(master);

	/* Release the GPIOs */
	release_copro_gpios(master);

	return rc;
}