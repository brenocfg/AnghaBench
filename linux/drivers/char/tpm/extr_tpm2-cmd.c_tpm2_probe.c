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
struct tpm_header {int /*<<< orphan*/  tag; } ;
struct tpm_chip {int /*<<< orphan*/  flags; } ;
struct tpm_buf {scalar_t__ data; } ;

/* Variables and functions */
 int TPM2_CAP_TPM_PROPERTIES ; 
 int /*<<< orphan*/  TPM2_CC_GET_CAPABILITY ; 
 scalar_t__ TPM2_ST_NO_SESSIONS ; 
 int /*<<< orphan*/  TPM_CHIP_FLAG_TPM2 ; 
 int TPM_PT_TOTAL_COMMANDS ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tpm_buf_append_u32 (struct tpm_buf*,int) ; 
 int /*<<< orphan*/  tpm_buf_destroy (struct tpm_buf*) ; 
 int tpm_buf_init (struct tpm_buf*,scalar_t__,int /*<<< orphan*/ ) ; 
 int tpm_transmit_cmd (struct tpm_chip*,struct tpm_buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int tpm2_probe(struct tpm_chip *chip)
{
	struct tpm_header *out;
	struct tpm_buf buf;
	int rc;

	rc = tpm_buf_init(&buf, TPM2_ST_NO_SESSIONS, TPM2_CC_GET_CAPABILITY);
	if (rc)
		return rc;
	tpm_buf_append_u32(&buf, TPM2_CAP_TPM_PROPERTIES);
	tpm_buf_append_u32(&buf, TPM_PT_TOTAL_COMMANDS);
	tpm_buf_append_u32(&buf, 1);
	rc = tpm_transmit_cmd(chip, &buf, 0, NULL);
	/* We ignore TPM return codes on purpose. */
	if (rc >=  0) {
		out = (struct tpm_header *)buf.data;
		if (be16_to_cpu(out->tag) == TPM2_ST_NO_SESSIONS)
			chip->flags |= TPM_CHIP_FLAG_TPM2;
	}
	tpm_buf_destroy(&buf);
	return 0;
}