#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tpm_chip {int dummy; } ;
struct i2c_client {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * client; int /*<<< orphan*/  locality; struct tpm_chip* chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  release_locality (struct tpm_chip*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tpm_chip_unregister (struct tpm_chip*) ; 
 TYPE_1__ tpm_dev ; 

__attribute__((used)) static int tpm_tis_i2c_remove(struct i2c_client *client)
{
	struct tpm_chip *chip = tpm_dev.chip;

	tpm_chip_unregister(chip);
	release_locality(chip, tpm_dev.locality, 1);
	tpm_dev.client = NULL;

	return 0;
}