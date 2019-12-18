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
struct TYPE_2__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int CONDUIT_HVC ; 
 int CONDUIT_INVALID ; 
 int CONDUIT_SMC ; 
 int /*<<< orphan*/  CONFIG_ACPI ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_disabled ; 
 scalar_t__ acpi_psci_use_hvc () ; 
 scalar_t__ of_property_read_string (struct device_node*,char*,char const**) ; 
 int /*<<< orphan*/  pr_warn (char*,...) ; 
 int /*<<< orphan*/ * sdei_firmware_call ; 
 int /*<<< orphan*/  sdei_smccc_hvc ; 
 int /*<<< orphan*/  sdei_smccc_smc ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 

__attribute__((used)) static int sdei_get_conduit(struct platform_device *pdev)
{
	const char *method;
	struct device_node *np = pdev->dev.of_node;

	sdei_firmware_call = NULL;
	if (np) {
		if (of_property_read_string(np, "method", &method)) {
			pr_warn("missing \"method\" property\n");
			return CONDUIT_INVALID;
		}

		if (!strcmp("hvc", method)) {
			sdei_firmware_call = &sdei_smccc_hvc;
			return CONDUIT_HVC;
		} else if (!strcmp("smc", method)) {
			sdei_firmware_call = &sdei_smccc_smc;
			return CONDUIT_SMC;
		}

		pr_warn("invalid \"method\" property: %s\n", method);
	} else if (IS_ENABLED(CONFIG_ACPI) && !acpi_disabled) {
		if (acpi_psci_use_hvc()) {
			sdei_firmware_call = &sdei_smccc_hvc;
			return CONDUIT_HVC;
		} else {
			sdei_firmware_call = &sdei_smccc_smc;
			return CONDUIT_SMC;
		}
	}

	return CONDUIT_INVALID;
}