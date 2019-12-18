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
struct vtpm_shared_page {size_t length; scalar_t__ state; } ;
struct tpm_private {int /*<<< orphan*/  read_queue; struct vtpm_shared_page* shr; } ;
struct tpm_chip {int /*<<< orphan*/  timeout_c; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ECANCELED ; 
 int EIO ; 
 int ETIME ; 
 unsigned int PAGE_SIZE ; 
 scalar_t__ VTPM_STATE_IDLE ; 
 int /*<<< orphan*/  VTPM_STATUS_RESULT ; 
 struct tpm_private* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 unsigned int shr_data_offset (struct vtpm_shared_page*) ; 
 int /*<<< orphan*/  vtpm_cancel (struct tpm_chip*) ; 
 scalar_t__ wait_for_tpm_stat (struct tpm_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int vtpm_recv(struct tpm_chip *chip, u8 *buf, size_t count)
{
	struct tpm_private *priv = dev_get_drvdata(&chip->dev);
	struct vtpm_shared_page *shr = priv->shr;
	unsigned int offset = shr_data_offset(shr);
	size_t length = shr->length;

	if (shr->state == VTPM_STATE_IDLE)
		return -ECANCELED;

	/* In theory the wait at the end of _send makes this one unnecessary */
	if (wait_for_tpm_stat(chip, VTPM_STATUS_RESULT, chip->timeout_c,
			&priv->read_queue, true) < 0) {
		vtpm_cancel(chip);
		return -ETIME;
	}

	if (offset > PAGE_SIZE)
		return -EIO;

	if (offset + length > PAGE_SIZE)
		length = PAGE_SIZE - offset;

	if (length > count)
		length = count;

	memcpy(buf, offset + (u8 *)shr, length);

	return length;
}