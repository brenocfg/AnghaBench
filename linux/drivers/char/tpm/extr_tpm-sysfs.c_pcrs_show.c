#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u32 ;
struct tpm_chip {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_3__ {int /*<<< orphan*/  num_pcrs; } ;
typedef  TYPE_1__ cap_t ;

/* Variables and functions */
 int /*<<< orphan*/  TPM_CAP_PROP_PCR ; 
 int TPM_DIGEST_SIZE ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 struct tpm_chip* to_tpm_chip (struct device*) ; 
 scalar_t__ tpm1_getcap (struct tpm_chip*,int /*<<< orphan*/ ,TYPE_1__*,char*,int) ; 
 scalar_t__ tpm1_pcr_read (struct tpm_chip*,scalar_t__,int*) ; 
 int /*<<< orphan*/  tpm_put_ops (struct tpm_chip*) ; 
 scalar_t__ tpm_try_get_ops (struct tpm_chip*) ; 

__attribute__((used)) static ssize_t pcrs_show(struct device *dev, struct device_attribute *attr,
			 char *buf)
{
	cap_t cap;
	u8 digest[TPM_DIGEST_SIZE];
	u32 i, j, num_pcrs;
	char *str = buf;
	struct tpm_chip *chip = to_tpm_chip(dev);

	if (tpm_try_get_ops(chip))
		return 0;

	if (tpm1_getcap(chip, TPM_CAP_PROP_PCR, &cap,
			"attempting to determine the number of PCRS",
			sizeof(cap.num_pcrs))) {
		tpm_put_ops(chip);
		return 0;
	}

	num_pcrs = be32_to_cpu(cap.num_pcrs);
	for (i = 0; i < num_pcrs; i++) {
		if (tpm1_pcr_read(chip, i, digest)) {
			str = buf;
			break;
		}
		str += sprintf(str, "PCR-%02d: ", i);
		for (j = 0; j < TPM_DIGEST_SIZE; j++)
			str += sprintf(str, "%02X ", digest[j]);
		str += sprintf(str, "\n");
	}
	tpm_put_ops(chip);
	return str - buf;
}