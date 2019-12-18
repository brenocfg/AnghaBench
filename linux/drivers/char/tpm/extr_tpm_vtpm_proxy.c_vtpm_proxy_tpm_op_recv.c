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
struct proxy_dev {int state; size_t resp_len; int /*<<< orphan*/  buf_lock; int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 size_t EIO ; 
 int EPIPE ; 
 int STATE_OPENED_FLAG ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,size_t,size_t) ; 
 struct proxy_dev* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vtpm_proxy_tpm_op_recv(struct tpm_chip *chip, u8 *buf, size_t count)
{
	struct proxy_dev *proxy_dev = dev_get_drvdata(&chip->dev);
	size_t len;

	/* process gone ? */
	mutex_lock(&proxy_dev->buf_lock);

	if (!(proxy_dev->state & STATE_OPENED_FLAG)) {
		mutex_unlock(&proxy_dev->buf_lock);
		return -EPIPE;
	}

	len = proxy_dev->resp_len;
	if (count < len) {
		dev_err(&chip->dev,
			"Invalid size in recv: count=%zd, resp_len=%zd\n",
			count, len);
		len = -EIO;
		goto out;
	}

	memcpy(buf, proxy_dev->buffer, len);
	proxy_dev->resp_len = 0;

out:
	mutex_unlock(&proxy_dev->buf_lock);

	return len;
}