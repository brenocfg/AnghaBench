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
struct TYPE_2__ {int /*<<< orphan*/  read; int /*<<< orphan*/  name; } ;
struct tpm_chip {int dev_num; TYPE_1__ hwrng; int /*<<< orphan*/  hwrng_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_HW_RANDOM_TPM ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int hwrng_register (TYPE_1__*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  tpm_hwrng_read ; 

__attribute__((used)) static int tpm_add_hwrng(struct tpm_chip *chip)
{
	if (!IS_ENABLED(CONFIG_HW_RANDOM_TPM))
		return 0;

	snprintf(chip->hwrng_name, sizeof(chip->hwrng_name),
		 "tpm-rng-%d", chip->dev_num);
	chip->hwrng.name = chip->hwrng_name;
	chip->hwrng.read = tpm_hwrng_read;
	return hwrng_register(&chip->hwrng);
}