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
struct tpm_chip {int /*<<< orphan*/  dev; } ;
struct proxy_dev {int state; size_t req_len; int /*<<< orphan*/  wq; int /*<<< orphan*/  buf_lock; int /*<<< orphan*/  buffer; scalar_t__ resp_len; } ;

/* Variables and functions */
 int EFAULT ; 
 int EIO ; 
 int EPIPE ; 
 int STATE_DRIVER_COMMAND ; 
 int STATE_OPENED_FLAG ; 
 int STATE_WAIT_RESPONSE_FLAG ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,size_t,int) ; 
 struct proxy_dev* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ vtpm_proxy_is_driver_command (struct tpm_chip*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vtpm_proxy_tpm_op_send(struct tpm_chip *chip, u8 *buf, size_t count)
{
	struct proxy_dev *proxy_dev = dev_get_drvdata(&chip->dev);

	if (count > sizeof(proxy_dev->buffer)) {
		dev_err(&chip->dev,
			"Invalid size in send: count=%zd, buffer size=%zd\n",
			count, sizeof(proxy_dev->buffer));
		return -EIO;
	}

	if (!(proxy_dev->state & STATE_DRIVER_COMMAND) &&
	    vtpm_proxy_is_driver_command(chip, buf, count))
		return -EFAULT;

	mutex_lock(&proxy_dev->buf_lock);

	if (!(proxy_dev->state & STATE_OPENED_FLAG)) {
		mutex_unlock(&proxy_dev->buf_lock);
		return -EPIPE;
	}

	proxy_dev->resp_len = 0;

	proxy_dev->req_len = count;
	memcpy(proxy_dev->buffer, buf, count);

	proxy_dev->state &= ~STATE_WAIT_RESPONSE_FLAG;

	mutex_unlock(&proxy_dev->buf_lock);

	wake_up_interruptible(&proxy_dev->wq);

	return 0;
}