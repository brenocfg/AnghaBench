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
typedef  int /*<<< orphan*/  u32 ;
struct sbefifo {TYPE_1__* fsi_dev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int SBEFIFO_EOT_RAISE ; 
 int /*<<< orphan*/  SBEFIFO_TIMEOUT_IN_CMD ; 
 int /*<<< orphan*/  SBEFIFO_TIMEOUT_START_CMD ; 
 int SBEFIFO_UP ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_vdbg (struct device*,char*,size_t,size_t,...) ; 
 size_t min (size_t,size_t) ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int sbefifo_regw (struct sbefifo*,int,int /*<<< orphan*/ ) ; 
 int sbefifo_up_write (struct sbefifo*,int /*<<< orphan*/ ) ; 
 size_t sbefifo_vacant (int /*<<< orphan*/ ) ; 
 int sbefifo_wait (struct sbefifo*,int,int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int sbefifo_send_command(struct sbefifo *sbefifo,
				const __be32 *command, size_t cmd_len)
{
	struct device *dev = &sbefifo->fsi_dev->dev;
	size_t len, chunk, vacant = 0, remaining = cmd_len;
	unsigned long timeout;
	u32 status;
	int rc;

	dev_vdbg(dev, "sending command (%zd words, cmd=%04x)\n",
		 cmd_len, be32_to_cpu(command[1]));

	/* As long as there's something to send */
	timeout = msecs_to_jiffies(SBEFIFO_TIMEOUT_START_CMD);
	while (remaining) {
		/* Wait for room in the FIFO */
		rc = sbefifo_wait(sbefifo, true, &status, timeout);
		if (rc < 0)
			return rc;
		timeout = msecs_to_jiffies(SBEFIFO_TIMEOUT_IN_CMD);

		vacant = sbefifo_vacant(status);
		len = chunk = min(vacant, remaining);

		dev_vdbg(dev, "  status=%08x vacant=%zd chunk=%zd\n",
			 status, vacant, chunk);

		/* Write as much as we can */
		while (len--) {
			rc = sbefifo_up_write(sbefifo, *(command++));
			if (rc) {
				dev_err(dev, "FSI error %d writing UP FIFO\n", rc);
				return rc;
			}
		}
		remaining -= chunk;
		vacant -= chunk;
	}

	/* If there's no room left, wait for some to write EOT */
	if (!vacant) {
		rc = sbefifo_wait(sbefifo, true, &status, timeout);
		if (rc)
			return rc;
	}

	/* Send an EOT */
	rc = sbefifo_regw(sbefifo, SBEFIFO_UP | SBEFIFO_EOT_RAISE, 0);
	if (rc)
		dev_err(dev, "FSI error %d writing EOT\n", rc);
	return rc;
}