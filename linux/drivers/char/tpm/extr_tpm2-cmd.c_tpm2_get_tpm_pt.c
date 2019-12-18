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
struct tpm_chip {int dummy; } ;
struct tpm_buf {int /*<<< orphan*/ * data; } ;
struct tpm2_get_cap_out {int /*<<< orphan*/  value; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int TPM2_CAP_TPM_PROPERTIES ; 
 int /*<<< orphan*/  TPM2_CC_GET_CAPABILITY ; 
 int /*<<< orphan*/  TPM2_ST_NO_SESSIONS ; 
 size_t TPM_HEADER_SIZE ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tpm_buf_append_u32 (struct tpm_buf*,int) ; 
 int /*<<< orphan*/  tpm_buf_destroy (struct tpm_buf*) ; 
 int tpm_buf_init (struct tpm_buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tpm_transmit_cmd (struct tpm_chip*,struct tpm_buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

ssize_t tpm2_get_tpm_pt(struct tpm_chip *chip, u32 property_id,  u32 *value,
			const char *desc)
{
	struct tpm2_get_cap_out *out;
	struct tpm_buf buf;
	int rc;

	rc = tpm_buf_init(&buf, TPM2_ST_NO_SESSIONS, TPM2_CC_GET_CAPABILITY);
	if (rc)
		return rc;
	tpm_buf_append_u32(&buf, TPM2_CAP_TPM_PROPERTIES);
	tpm_buf_append_u32(&buf, property_id);
	tpm_buf_append_u32(&buf, 1);
	rc = tpm_transmit_cmd(chip, &buf, 0, NULL);
	if (!rc) {
		out = (struct tpm2_get_cap_out *)
			&buf.data[TPM_HEADER_SIZE];
		*value = be32_to_cpu(out->value);
	}
	tpm_buf_destroy(&buf);
	return rc;
}