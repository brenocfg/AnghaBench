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
struct tpm_space {int dummy; } ;
struct tpm_header {void* return_code; int /*<<< orphan*/  tag; void* length; } ;
struct tpm_chip {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int TPM2_RC_COMMAND_CODE ; 
 int /*<<< orphan*/  TPM2_ST_NO_SESSIONS ; 
 int TSS2_RESMGR_TPM_RC_LAYER ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int) ; 
 int tpm2_commit_space (struct tpm_chip*,struct tpm_space*,int /*<<< orphan*/ *,int*) ; 
 int tpm2_prepare_space (struct tpm_chip*,struct tpm_space*,int /*<<< orphan*/ *,size_t) ; 
 int tpm_transmit (struct tpm_chip*,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static ssize_t tpm_dev_transmit(struct tpm_chip *chip, struct tpm_space *space,
				u8 *buf, size_t bufsiz)
{
	struct tpm_header *header = (void *)buf;
	ssize_t ret, len;

	ret = tpm2_prepare_space(chip, space, buf, bufsiz);
	/* If the command is not implemented by the TPM, synthesize a
	 * response with a TPM2_RC_COMMAND_CODE return for user-space.
	 */
	if (ret == -EOPNOTSUPP) {
		header->length = cpu_to_be32(sizeof(*header));
		header->tag = cpu_to_be16(TPM2_ST_NO_SESSIONS);
		header->return_code = cpu_to_be32(TPM2_RC_COMMAND_CODE |
						  TSS2_RESMGR_TPM_RC_LAYER);
		ret = sizeof(*header);
	}
	if (ret)
		goto out_rc;

	len = tpm_transmit(chip, buf, bufsiz);
	if (len < 0)
		ret = len;

	if (!ret)
		ret = tpm2_commit_space(chip, space, buf, &len);

out_rc:
	return ret ? ret : len;
}