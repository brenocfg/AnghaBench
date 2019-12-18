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
struct tpm_chip {int dummy; } ;
struct tpm_buf {void* data; } ;

/* Variables and functions */
 int ENODEV ; 
 struct tpm_chip* tpm_find_get_ops (struct tpm_chip*) ; 
 int /*<<< orphan*/  tpm_put_ops (struct tpm_chip*) ; 
 int tpm_transmit_cmd (struct tpm_chip*,struct tpm_buf*,int /*<<< orphan*/ ,char*) ; 

int tpm_send(struct tpm_chip *chip, void *cmd, size_t buflen)
{
	struct tpm_buf buf;
	int rc;

	chip = tpm_find_get_ops(chip);
	if (!chip)
		return -ENODEV;

	buf.data = cmd;
	rc = tpm_transmit_cmd(chip, &buf, 0, "attempting to a send a command");

	tpm_put_ops(chip);
	return rc;
}