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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct tpm_tis_data {int /*<<< orphan*/  read_queue; int /*<<< orphan*/  locality; } ;
struct tpm_chip {int flags; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ETIME ; 
 int TPM_CHIP_FLAG_IRQ ; 
 int /*<<< orphan*/  TPM_STS (int /*<<< orphan*/ ) ; 
 int TPM_STS_DATA_AVAIL ; 
 int /*<<< orphan*/  TPM_STS_GO ; 
 int TPM_STS_VALID ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 struct tpm_tis_data* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 unsigned long tpm_calc_ordinal_duration (struct tpm_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tpm_tis_ready (struct tpm_chip*) ; 
 int tpm_tis_send_data (struct tpm_chip*,int /*<<< orphan*/  const*,size_t) ; 
 int tpm_tis_write8 (struct tpm_tis_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ wait_for_tpm_stat (struct tpm_chip*,int,unsigned long,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int tpm_tis_send_main(struct tpm_chip *chip, const u8 *buf, size_t len)
{
	struct tpm_tis_data *priv = dev_get_drvdata(&chip->dev);
	int rc;
	u32 ordinal;
	unsigned long dur;

	rc = tpm_tis_send_data(chip, buf, len);
	if (rc < 0)
		return rc;

	/* go and do it */
	rc = tpm_tis_write8(priv, TPM_STS(priv->locality), TPM_STS_GO);
	if (rc < 0)
		goto out_err;

	if (chip->flags & TPM_CHIP_FLAG_IRQ) {
		ordinal = be32_to_cpu(*((__be32 *) (buf + 6)));

		dur = tpm_calc_ordinal_duration(chip, ordinal);
		if (wait_for_tpm_stat
		    (chip, TPM_STS_DATA_AVAIL | TPM_STS_VALID, dur,
		     &priv->read_queue, false) < 0) {
			rc = -ETIME;
			goto out_err;
		}
	}
	return 0;
out_err:
	tpm_tis_ready(chip);
	return rc;
}