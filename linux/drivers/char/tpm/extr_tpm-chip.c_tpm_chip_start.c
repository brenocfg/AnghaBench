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
struct tpm_chip {int locality; } ;

/* Variables and functions */
 int /*<<< orphan*/  tpm_clk_disable (struct tpm_chip*) ; 
 int /*<<< orphan*/  tpm_clk_enable (struct tpm_chip*) ; 
 int tpm_cmd_ready (struct tpm_chip*) ; 
 int /*<<< orphan*/  tpm_relinquish_locality (struct tpm_chip*) ; 
 int tpm_request_locality (struct tpm_chip*) ; 

int tpm_chip_start(struct tpm_chip *chip)
{
	int ret;

	tpm_clk_enable(chip);

	if (chip->locality == -1) {
		ret = tpm_request_locality(chip);
		if (ret) {
			tpm_clk_disable(chip);
			return ret;
		}
	}

	ret = tpm_cmd_ready(chip);
	if (ret) {
		tpm_relinquish_locality(chip);
		tpm_clk_disable(chip);
		return ret;
	}

	return 0;
}