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
struct tpm_class_ops {int dummy; } ;
struct tpm_chip {int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct tpm_chip* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct tpm_chip*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct tpm_chip*) ; 
 int devm_add_action_or_reset (struct device*,void (*) (void*),int /*<<< orphan*/ *) ; 
 scalar_t__ put_device ; 
 struct tpm_chip* tpm_chip_alloc (struct device*,struct tpm_class_ops const*) ; 

struct tpm_chip *tpmm_chip_alloc(struct device *pdev,
				 const struct tpm_class_ops *ops)
{
	struct tpm_chip *chip;
	int rc;

	chip = tpm_chip_alloc(pdev, ops);
	if (IS_ERR(chip))
		return chip;

	rc = devm_add_action_or_reset(pdev,
				      (void (*)(void *)) put_device,
				      &chip->dev);
	if (rc)
		return ERR_PTR(rc);

	dev_set_drvdata(pdev, chip);

	return chip;
}