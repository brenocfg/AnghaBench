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
typedef  int u8 ;
struct tpm_tis_data {int manufacturer_id; } ;
struct tpm_chip {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int TPM_STS_COMMAND_READY ; 
 int TPM_STS_VALID ; 
#define  TPM_VID_STM 129 
#define  TPM_VID_WINBOND 128 
 struct tpm_tis_data* dev_get_drvdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool tpm_tis_req_canceled(struct tpm_chip *chip, u8 status)
{
	struct tpm_tis_data *priv = dev_get_drvdata(&chip->dev);

	switch (priv->manufacturer_id) {
	case TPM_VID_WINBOND:
		return ((status == TPM_STS_VALID) ||
			(status == (TPM_STS_VALID | TPM_STS_COMMAND_READY)));
	case TPM_VID_STM:
		return (status == (TPM_STS_VALID | TPM_STS_COMMAND_READY));
	default:
		return (status == TPM_STS_COMMAND_READY);
	}
}