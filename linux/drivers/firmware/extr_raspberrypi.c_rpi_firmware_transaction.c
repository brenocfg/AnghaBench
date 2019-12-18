#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct rpi_firmware {TYPE_1__ cl; int /*<<< orphan*/  c; int /*<<< orphan*/  chan; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  HZ ; 
 int MBOX_MSG (int,int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int mbox_send_message (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  transaction_lock ; 
 scalar_t__ wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rpi_firmware_transaction(struct rpi_firmware *fw, u32 chan, u32 data)
{
	u32 message = MBOX_MSG(chan, data);
	int ret;

	WARN_ON(data & 0xf);

	mutex_lock(&transaction_lock);
	reinit_completion(&fw->c);
	ret = mbox_send_message(fw->chan, &message);
	if (ret >= 0) {
		if (wait_for_completion_timeout(&fw->c, HZ)) {
			ret = 0;
		} else {
			ret = -ETIMEDOUT;
			WARN_ONCE(1, "Firmware transaction timeout");
		}
	} else {
		dev_err(fw->cl.dev, "mbox_send_message returned %d\n", ret);
	}
	mutex_unlock(&transaction_lock);

	return ret;
}