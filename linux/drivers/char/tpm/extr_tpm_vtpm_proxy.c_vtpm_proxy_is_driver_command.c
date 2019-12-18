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
struct tpm_header {int /*<<< orphan*/  ordinal; } ;
struct tpm_chip {int flags; } ;

/* Variables and functions */
#define  TPM2_CC_SET_LOCALITY 129 
 int TPM_CHIP_FLAG_TPM2 ; 
#define  TPM_ORD_SET_LOCALITY 128 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vtpm_proxy_is_driver_command(struct tpm_chip *chip,
					u8 *buf, size_t count)
{
	struct tpm_header *hdr = (struct tpm_header *)buf;

	if (count < sizeof(struct tpm_header))
		return 0;

	if (chip->flags & TPM_CHIP_FLAG_TPM2) {
		switch (be32_to_cpu(hdr->ordinal)) {
		case TPM2_CC_SET_LOCALITY:
			return 1;
		}
	} else {
		switch (be32_to_cpu(hdr->ordinal)) {
		case TPM_ORD_SET_LOCALITY:
			return 1;
		}
	}
	return 0;
}