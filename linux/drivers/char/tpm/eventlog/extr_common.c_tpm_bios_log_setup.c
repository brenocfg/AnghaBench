#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * seqops; struct tpm_chip* chip; } ;
struct TYPE_3__ {int /*<<< orphan*/ * seqops; struct tpm_chip* chip; } ;
struct tpm_chip {int flags; int /*<<< orphan*/ ** bios_dir; TYPE_2__ ascii_log_seqops; TYPE_1__ bin_log_seqops; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EFI_TCG2_EVENT_LOG_FORMAT_TCG_2 ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int TPM_CHIP_FLAG_TPM2 ; 
 char* dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * securityfs_create_dir (char const*,int /*<<< orphan*/ *) ; 
 void* securityfs_create_file (char*,int,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tpm1_ascii_b_measurements_seqops ; 
 int /*<<< orphan*/  tpm1_binary_b_measurements_seqops ; 
 int /*<<< orphan*/  tpm2_binary_b_measurements_seqops ; 
 int /*<<< orphan*/  tpm_bios_log_teardown (struct tpm_chip*) ; 
 int /*<<< orphan*/  tpm_bios_measurements_ops ; 
 int tpm_read_log (struct tpm_chip*) ; 

int tpm_bios_log_setup(struct tpm_chip *chip)
{
	const char *name = dev_name(&chip->dev);
	unsigned int cnt;
	int log_version;
	int rc = 0;

	rc = tpm_read_log(chip);
	if (rc < 0)
		return rc;
	log_version = rc;

	cnt = 0;
	chip->bios_dir[cnt] = securityfs_create_dir(name, NULL);
	/* NOTE: securityfs_create_dir can return ENODEV if securityfs is
	 * compiled out. The caller should ignore the ENODEV return code.
	 */
	if (IS_ERR(chip->bios_dir[cnt]))
		goto err;
	cnt++;

	chip->bin_log_seqops.chip = chip;
	if (log_version == EFI_TCG2_EVENT_LOG_FORMAT_TCG_2)
		chip->bin_log_seqops.seqops =
			&tpm2_binary_b_measurements_seqops;
	else
		chip->bin_log_seqops.seqops =
			&tpm1_binary_b_measurements_seqops;


	chip->bios_dir[cnt] =
	    securityfs_create_file("binary_bios_measurements",
				   0440, chip->bios_dir[0],
				   (void *)&chip->bin_log_seqops,
				   &tpm_bios_measurements_ops);
	if (IS_ERR(chip->bios_dir[cnt]))
		goto err;
	cnt++;

	if (!(chip->flags & TPM_CHIP_FLAG_TPM2)) {

		chip->ascii_log_seqops.chip = chip;
		chip->ascii_log_seqops.seqops =
			&tpm1_ascii_b_measurements_seqops;

		chip->bios_dir[cnt] =
			securityfs_create_file("ascii_bios_measurements",
					       0440, chip->bios_dir[0],
					       (void *)&chip->ascii_log_seqops,
					       &tpm_bios_measurements_ops);
		if (IS_ERR(chip->bios_dir[cnt]))
			goto err;
		cnt++;
	}

	return 0;

err:
	rc = PTR_ERR(chip->bios_dir[cnt]);
	chip->bios_dir[cnt] = NULL;
	tpm_bios_log_teardown(chip);
	return rc;
}