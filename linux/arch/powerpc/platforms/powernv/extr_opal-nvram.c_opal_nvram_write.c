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
typedef  size_t ssize_t ;
typedef  scalar_t__ s64 ;
typedef  int loff_t ;

/* Variables and functions */
 size_t EIO ; 
 scalar_t__ OPAL_BUSY ; 
 int /*<<< orphan*/  OPAL_BUSY_DELAY_MS ; 
 scalar_t__ OPAL_BUSY_EVENT ; 
 int /*<<< orphan*/  __pa (char*) ; 
 scalar_t__ in_interrupt () ; 
 scalar_t__ irqs_disabled () ; 
 int /*<<< orphan*/  mdelay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int nvram_size ; 
 int /*<<< orphan*/  opal_poll_events (int /*<<< orphan*/ *) ; 
 scalar_t__ opal_write_nvram (int /*<<< orphan*/ ,size_t,int) ; 

__attribute__((used)) static ssize_t opal_nvram_write(char *buf, size_t count, loff_t *index)
{
	s64 rc = OPAL_BUSY;
	int off;

	if (*index >= nvram_size)
		return 0;
	off = *index;
	if ((off + count) > nvram_size)
		count = nvram_size - off;

	while (rc == OPAL_BUSY || rc == OPAL_BUSY_EVENT) {
		rc = opal_write_nvram(__pa(buf), count, off);
		if (rc == OPAL_BUSY_EVENT) {
			if (in_interrupt() || irqs_disabled())
				mdelay(OPAL_BUSY_DELAY_MS);
			else
				msleep(OPAL_BUSY_DELAY_MS);
			opal_poll_events(NULL);
		} else if (rc == OPAL_BUSY) {
			if (in_interrupt() || irqs_disabled())
				mdelay(OPAL_BUSY_DELAY_MS);
			else
				msleep(OPAL_BUSY_DELAY_MS);
		}
	}

	if (rc)
		return -EIO;

	*index += count;
	return count;
}