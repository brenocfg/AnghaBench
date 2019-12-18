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
struct tpm_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tpm_clk_disable (struct tpm_chip*) ; 
 int /*<<< orphan*/  tpm_go_idle (struct tpm_chip*) ; 
 int /*<<< orphan*/  tpm_relinquish_locality (struct tpm_chip*) ; 

void tpm_chip_stop(struct tpm_chip *chip)
{
	tpm_go_idle(chip);
	tpm_relinquish_locality(chip);
	tpm_clk_disable(chip);
}