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
struct vtpm_shared_page {size_t length; int /*<<< orphan*/  state; } ;
struct tpm_private {int /*<<< orphan*/  read_queue; int /*<<< orphan*/  evtchn; struct vtpm_shared_page* shr; } ;
struct tpm_header {int /*<<< orphan*/  ordinal; } ;
struct tpm_chip {unsigned long timeout_c; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETIME ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  VTPM_STATE_SUBMIT ; 
 int /*<<< orphan*/  VTPM_STATUS_IDLE ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 struct tpm_private* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  notify_remote_via_evtchn (int /*<<< orphan*/ ) ; 
 unsigned int shr_data_offset (struct vtpm_shared_page*) ; 
 unsigned long tpm_calc_ordinal_duration (struct tpm_chip*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vtpm_cancel (struct tpm_chip*) ; 
 scalar_t__ wait_for_tpm_stat (struct tpm_chip*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int vtpm_send(struct tpm_chip *chip, u8 *buf, size_t count)
{
	struct tpm_private *priv = dev_get_drvdata(&chip->dev);
	struct vtpm_shared_page *shr = priv->shr;
	unsigned int offset = shr_data_offset(shr);

	u32 ordinal;
	unsigned long duration;

	if (offset > PAGE_SIZE)
		return -EINVAL;

	if (offset + count > PAGE_SIZE)
		return -EINVAL;

	/* Wait for completion of any existing command or cancellation */
	if (wait_for_tpm_stat(chip, VTPM_STATUS_IDLE, chip->timeout_c,
			&priv->read_queue, true) < 0) {
		vtpm_cancel(chip);
		return -ETIME;
	}

	memcpy(offset + (u8 *)shr, buf, count);
	shr->length = count;
	barrier();
	shr->state = VTPM_STATE_SUBMIT;
	wmb();
	notify_remote_via_evtchn(priv->evtchn);

	ordinal = be32_to_cpu(((struct tpm_header *)buf)->ordinal);
	duration = tpm_calc_ordinal_duration(chip, ordinal);

	if (wait_for_tpm_stat(chip, VTPM_STATUS_IDLE, duration,
			&priv->read_queue, true) < 0) {
		/* got a signal or timeout, try to cancel */
		vtpm_cancel(chip);
		return -ETIME;
	}

	return 0;
}