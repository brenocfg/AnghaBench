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
struct proxy_dev {int state; int /*<<< orphan*/  buf_lock; } ;

/* Variables and functions */
 int STATE_OPENED_FLAG ; 
 struct proxy_dev* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool vtpm_proxy_tpm_req_canceled(struct tpm_chip  *chip, u8 status)
{
	struct proxy_dev *proxy_dev = dev_get_drvdata(&chip->dev);
	bool ret;

	mutex_lock(&proxy_dev->buf_lock);

	ret = !(proxy_dev->state & STATE_OPENED_FLAG);

	mutex_unlock(&proxy_dev->buf_lock);

	return ret;
}