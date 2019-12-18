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
struct sbefifo {int broken; TYPE_1__* fsi_dev; } ;
struct iov_iter {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int EFAULT ; 
 int EIO ; 
 int EOVERFLOW ; 
 int SBEFIFO_DOWN ; 
 int SBEFIFO_EOT_ACK ; 
 int /*<<< orphan*/  SBEFIFO_TIMEOUT_IN_RSP ; 
 int /*<<< orphan*/  SBEFIFO_TIMEOUT_START_RSP ; 
 int copy_to_iter (int /*<<< orphan*/ *,int,struct iov_iter*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_vdbg (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,size_t) ; 
 int iov_iter_count (struct iov_iter*) ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int sbefifo_down_read (struct sbefifo*,int /*<<< orphan*/ *) ; 
 int sbefifo_eot_set (int) ; 
 size_t sbefifo_populated (int) ; 
 int sbefifo_regw (struct sbefifo*,int,int /*<<< orphan*/ ) ; 
 int sbefifo_wait (struct sbefifo*,int,int*,unsigned long) ; 

__attribute__((used)) static int sbefifo_read_response(struct sbefifo *sbefifo, struct iov_iter *response)
{
	struct device *dev = &sbefifo->fsi_dev->dev;
	u32 status, eot_set;
	unsigned long timeout;
	bool overflow = false;
	__be32 data;
	size_t len;
	int rc;

	dev_vdbg(dev, "reading response, buflen = %zd\n", iov_iter_count(response));

	timeout = msecs_to_jiffies(SBEFIFO_TIMEOUT_START_RSP);
	for (;;) {
		/* Grab FIFO status (this will handle parity errors) */
		rc = sbefifo_wait(sbefifo, false, &status, timeout);
		if (rc < 0)
			return rc;
		timeout = msecs_to_jiffies(SBEFIFO_TIMEOUT_IN_RSP);

		/* Decode status */
		len = sbefifo_populated(status);
		eot_set = sbefifo_eot_set(status);

		dev_vdbg(dev, "  chunk size %zd eot_set=0x%x\n", len, eot_set);

		/* Go through the chunk */
		while(len--) {
			/* Read the data */
			rc = sbefifo_down_read(sbefifo, &data);
			if (rc < 0)
				return rc;

			/* Was it an EOT ? */
			if (eot_set & 0x80) {
				/*
				 * There should be nothing else in the FIFO,
				 * if there is, mark broken, this will force
				 * a reset on next use, but don't fail the
				 * command.
				 */
				if (len) {
					dev_warn(dev, "FIFO read hit"
						 " EOT with still %zd data\n",
						 len);
					sbefifo->broken = true;
				}

				/* We are done */
				rc = sbefifo_regw(sbefifo,
						  SBEFIFO_DOWN | SBEFIFO_EOT_ACK, 0);

				/*
				 * If that write fail, still complete the request but mark
				 * the fifo as broken for subsequent reset (not much else
				 * we can do here).
				 */
				if (rc) {
					dev_err(dev, "FSI error %d ack'ing EOT\n", rc);
					sbefifo->broken = true;
				}

				/* Tell whether we overflowed */
				return overflow ? -EOVERFLOW : 0;
			}

			/* Store it if there is room */
			if (iov_iter_count(response) >= sizeof(__be32)) {
				if (copy_to_iter(&data, sizeof(__be32), response) < sizeof(__be32))
					return -EFAULT;
			} else {
				dev_vdbg(dev, "Response overflowed !\n");

				overflow = true;
			}

			/* Next EOT bit */
			eot_set <<= 1;
		}
	}
	/* Shouldn't happen */
	return -EIO;
}