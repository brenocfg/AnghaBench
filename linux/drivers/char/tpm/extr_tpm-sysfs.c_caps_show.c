#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tpm_chip {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_6__ {int Major; int Minor; int revMajor; int revMinor; } ;
struct TYPE_5__ {int Major; int Minor; int revMajor; int revMinor; } ;
struct TYPE_7__ {TYPE_2__ tpm_version; TYPE_1__ tpm_version_1_2; int /*<<< orphan*/  manufacturer_id; } ;
typedef  TYPE_3__ cap_t ;

/* Variables and functions */
 int /*<<< orphan*/  TPM_CAP_PROP_MANUFACTURER ; 
 int /*<<< orphan*/  TPM_CAP_VERSION_1_1 ; 
 int /*<<< orphan*/  TPM_CAP_VERSION_1_2 ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,...) ; 
 struct tpm_chip* to_tpm_chip (struct device*) ; 
 int tpm1_getcap (struct tpm_chip*,int /*<<< orphan*/ ,TYPE_3__*,char*,int) ; 
 int /*<<< orphan*/  tpm_put_ops (struct tpm_chip*) ; 
 scalar_t__ tpm_try_get_ops (struct tpm_chip*) ; 

__attribute__((used)) static ssize_t caps_show(struct device *dev, struct device_attribute *attr,
			 char *buf)
{
	struct tpm_chip *chip = to_tpm_chip(dev);
	ssize_t rc = 0;
	char *str = buf;
	cap_t cap;

	if (tpm_try_get_ops(chip))
		return 0;

	if (tpm1_getcap(chip, TPM_CAP_PROP_MANUFACTURER, &cap,
			"attempting to determine the manufacturer",
			sizeof(cap.manufacturer_id)))
		goto out_ops;

	str += sprintf(str, "Manufacturer: 0x%x\n",
		       be32_to_cpu(cap.manufacturer_id));

	/* Try to get a TPM version 1.2 TPM_CAP_VERSION_INFO */
	rc = tpm1_getcap(chip, TPM_CAP_VERSION_1_2, &cap,
			 "attempting to determine the 1.2 version",
			 sizeof(cap.tpm_version_1_2));
	if (!rc) {
		str += sprintf(str,
			       "TCG version: %d.%d\nFirmware version: %d.%d\n",
			       cap.tpm_version_1_2.Major,
			       cap.tpm_version_1_2.Minor,
			       cap.tpm_version_1_2.revMajor,
			       cap.tpm_version_1_2.revMinor);
	} else {
		/* Otherwise just use TPM_STRUCT_VER */
		if (tpm1_getcap(chip, TPM_CAP_VERSION_1_1, &cap,
				"attempting to determine the 1.1 version",
				sizeof(cap.tpm_version)))
			goto out_ops;
		str += sprintf(str,
			       "TCG version: %d.%d\nFirmware version: %d.%d\n",
			       cap.tpm_version.Major,
			       cap.tpm_version.Minor,
			       cap.tpm_version.revMajor,
			       cap.tpm_version.revMinor);
	}
	rc = str - buf;
out_ops:
	tpm_put_ops(chip);
	return rc;
}