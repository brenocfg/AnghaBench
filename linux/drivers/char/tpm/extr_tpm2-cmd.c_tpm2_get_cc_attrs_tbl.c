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
typedef  int u32 ;
struct tpm_chip {int* cc_attrs_tbl; int nr_commands; int /*<<< orphan*/  dev; } ;
struct tpm_buf {int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int EFAULT ; 
 int ENODEV ; 
 int GENMASK (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int TPM2_CAP_COMMANDS ; 
 int TPM2_CC_ATTR_CHANDLES ; 
 int TPM2_CC_CONTEXT_SAVE ; 
 int TPM2_CC_FIRST ; 
 int TPM2_CC_FLUSH_CONTEXT ; 
 int /*<<< orphan*/  TPM2_CC_GET_CAPABILITY ; 
 int /*<<< orphan*/  TPM2_ST_NO_SESSIONS ; 
 int TPM_HEADER_SIZE ; 
 int /*<<< orphan*/  TPM_PT_TOTAL_COMMANDS ; 
 int be32_to_cpup (int /*<<< orphan*/ *) ; 
 int* devm_kcalloc (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int tpm2_get_tpm_pt (struct tpm_chip*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tpm_buf_append_u32 (struct tpm_buf*,int) ; 
 int /*<<< orphan*/  tpm_buf_destroy (struct tpm_buf*) ; 
 int tpm_buf_init (struct tpm_buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tpm_transmit_cmd (struct tpm_chip*,struct tpm_buf*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tpm2_get_cc_attrs_tbl(struct tpm_chip *chip)
{
	struct tpm_buf buf;
	u32 nr_commands;
	__be32 *attrs;
	u32 cc;
	int i;
	int rc;

	rc = tpm2_get_tpm_pt(chip, TPM_PT_TOTAL_COMMANDS, &nr_commands, NULL);
	if (rc)
		goto out;

	if (nr_commands > 0xFFFFF) {
		rc = -EFAULT;
		goto out;
	}

	chip->cc_attrs_tbl = devm_kcalloc(&chip->dev, 4, nr_commands,
					  GFP_KERNEL);

	rc = tpm_buf_init(&buf, TPM2_ST_NO_SESSIONS, TPM2_CC_GET_CAPABILITY);
	if (rc)
		goto out;

	tpm_buf_append_u32(&buf, TPM2_CAP_COMMANDS);
	tpm_buf_append_u32(&buf, TPM2_CC_FIRST);
	tpm_buf_append_u32(&buf, nr_commands);

	rc = tpm_transmit_cmd(chip, &buf, 9 + 4 * nr_commands, NULL);
	if (rc) {
		tpm_buf_destroy(&buf);
		goto out;
	}

	if (nr_commands !=
	    be32_to_cpup((__be32 *)&buf.data[TPM_HEADER_SIZE + 5])) {
		tpm_buf_destroy(&buf);
		goto out;
	}

	chip->nr_commands = nr_commands;

	attrs = (__be32 *)&buf.data[TPM_HEADER_SIZE + 9];
	for (i = 0; i < nr_commands; i++, attrs++) {
		chip->cc_attrs_tbl[i] = be32_to_cpup(attrs);
		cc = chip->cc_attrs_tbl[i] & 0xFFFF;

		if (cc == TPM2_CC_CONTEXT_SAVE || cc == TPM2_CC_FLUSH_CONTEXT) {
			chip->cc_attrs_tbl[i] &=
				~(GENMASK(2, 0) << TPM2_CC_ATTR_CHANDLES);
			chip->cc_attrs_tbl[i] |= 1 << TPM2_CC_ATTR_CHANDLES;
		}
	}

	tpm_buf_destroy(&buf);

out:
	if (rc > 0)
		rc = -ENODEV;
	return rc;
}