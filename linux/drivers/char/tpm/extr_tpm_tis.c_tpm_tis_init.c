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
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;
struct tpm_tis_tcg_phy {TYPE_1__ priv; int /*<<< orphan*/  iobase; } ;
struct tpm_info {int irq; int /*<<< orphan*/  res; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_COMPANION (struct device*) ; 
 int /*<<< orphan*/  ACPI_HANDLE (struct device*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TPM_TIS_ITPM_WORKAROUND ; 
 int check_acpi_tpm2 (struct device*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,int /*<<< orphan*/ *) ; 
 struct tpm_tis_tcg_phy* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ interrupts ; 
 scalar_t__ is_itpm (int /*<<< orphan*/ ) ; 
 scalar_t__ itpm ; 
 int /*<<< orphan*/  tpm_tcg ; 
 int tpm_tis_core_init (struct device*,TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tpm_tis_init(struct device *dev, struct tpm_info *tpm_info)
{
	struct tpm_tis_tcg_phy *phy;
	int irq = -1;
	int rc;

	rc = check_acpi_tpm2(dev);
	if (rc)
		return rc;

	phy = devm_kzalloc(dev, sizeof(struct tpm_tis_tcg_phy), GFP_KERNEL);
	if (phy == NULL)
		return -ENOMEM;

	phy->iobase = devm_ioremap_resource(dev, &tpm_info->res);
	if (IS_ERR(phy->iobase))
		return PTR_ERR(phy->iobase);

	if (interrupts)
		irq = tpm_info->irq;

	if (itpm || is_itpm(ACPI_COMPANION(dev)))
		phy->priv.flags |= TPM_TIS_ITPM_WORKAROUND;

	return tpm_tis_core_init(dev, &phy->priv, irq, &tpm_tcg,
				 ACPI_HANDLE(dev));
}