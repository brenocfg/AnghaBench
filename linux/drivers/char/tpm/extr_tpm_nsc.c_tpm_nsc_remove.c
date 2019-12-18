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
struct tpm_nsc_priv {int /*<<< orphan*/  base; } ;
struct device {int dummy; } ;
struct tpm_chip {struct device dev; } ;

/* Variables and functions */
 void* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tpm_chip_unregister (struct tpm_chip*) ; 

__attribute__((used)) static void tpm_nsc_remove(struct device *dev)
{
	struct tpm_chip *chip = dev_get_drvdata(dev);
	struct tpm_nsc_priv *priv = dev_get_drvdata(&chip->dev);

	tpm_chip_unregister(chip);
	release_region(priv->base, 2);
}