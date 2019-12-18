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
typedef  scalar_t__ u32 ;
struct hwicap_drvdata {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int EIO ; 
 scalar_t__ XHI_MAX_RETRIES ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ fifo_icap_busy (struct hwicap_drvdata*) ; 
 int /*<<< orphan*/  fifo_icap_fifo_write (struct hwicap_drvdata*,scalar_t__) ; 
 int /*<<< orphan*/  fifo_icap_start_config (struct hwicap_drvdata*) ; 
 scalar_t__ fifo_icap_write_fifo_vacancy (struct hwicap_drvdata*) ; 

int fifo_icap_set_configuration(struct hwicap_drvdata *drvdata,
		u32 *frame_buffer, u32 num_words)
{

	u32 write_fifo_vacancy = 0;
	u32 retries = 0;
	u32 remaining_words;

	dev_dbg(drvdata->dev, "fifo_set_configuration\n");

	/*
	 * Check if the ICAP device is Busy with the last Read/Write
	 */
	if (fifo_icap_busy(drvdata))
		return -EBUSY;

	/*
	 * Set up the buffer pointer and the words to be transferred.
	 */
	remaining_words = num_words;

	while (remaining_words > 0) {
		/*
		 * Wait until we have some data in the fifo.
		 */
		while (write_fifo_vacancy == 0) {
			write_fifo_vacancy =
				fifo_icap_write_fifo_vacancy(drvdata);
			retries++;
			if (retries > XHI_MAX_RETRIES)
				return -EIO;
		}

		/*
		 * Write data into the Write FIFO.
		 */
		while ((write_fifo_vacancy != 0) &&
				(remaining_words > 0)) {
			fifo_icap_fifo_write(drvdata, *frame_buffer);

			remaining_words--;
			write_fifo_vacancy--;
			frame_buffer++;
		}
		/* Start pushing whatever is in the FIFO into the ICAP. */
		fifo_icap_start_config(drvdata);
	}

	/* Wait until the write has finished. */
	while (fifo_icap_busy(drvdata)) {
		retries++;
		if (retries > XHI_MAX_RETRIES)
			break;
	}

	dev_dbg(drvdata->dev, "done fifo_set_configuration\n");

	/*
	 * If the requested number of words have not been read from
	 * the device then indicate failure.
	 */
	if (remaining_words != 0)
		return -EIO;

	return 0;
}