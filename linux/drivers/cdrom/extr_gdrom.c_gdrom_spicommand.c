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

/* Variables and functions */
 int /*<<< orphan*/  GDROM_ALTSTATUS_REG ; 
 int /*<<< orphan*/  GDROM_BCH_REG ; 
 int /*<<< orphan*/  GDROM_BCL_REG ; 
 int GDROM_COM_PACKET ; 
 int /*<<< orphan*/  GDROM_DATA_REG ; 
 unsigned long GDROM_DEFAULT_TIMEOUT ; 
 int /*<<< orphan*/  GDROM_ERROR_REG ; 
 int /*<<< orphan*/  GDROM_INTSEC_REG ; 
 int /*<<< orphan*/  GDROM_SECNUM_REG ; 
 int /*<<< orphan*/  GDROM_STATUSCOMMAND_REG ; 
 int /*<<< orphan*/  __raw_writeb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  gdrom_data_request () ; 
 int /*<<< orphan*/  gdrom_getsense (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gdrom_wait_clrbusy () ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  outsw (int /*<<< orphan*/ ,short*,int) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static void gdrom_spicommand(void *spi_string, int buflen)
{
	short *cmd = spi_string;
	unsigned long timeout;

	/* ensure IRQ_WAIT is set */
	__raw_writeb(0x08, GDROM_ALTSTATUS_REG);
	/* specify how many bytes we expect back */
	__raw_writeb(buflen & 0xFF, GDROM_BCL_REG);
	__raw_writeb((buflen >> 8) & 0xFF, GDROM_BCH_REG);
	/* other parameters */
	__raw_writeb(0, GDROM_INTSEC_REG);
	__raw_writeb(0, GDROM_SECNUM_REG);
	__raw_writeb(0, GDROM_ERROR_REG);
	/* Wait until we can go */
	if (!gdrom_wait_clrbusy()) {
		gdrom_getsense(NULL);
		return;
	}
	timeout = jiffies + GDROM_DEFAULT_TIMEOUT;
	__raw_writeb(GDROM_COM_PACKET, GDROM_STATUSCOMMAND_REG);
	while (!gdrom_data_request() && time_before(jiffies, timeout))
		cpu_relax();
	if (!time_before(jiffies, timeout + 1)) {
		gdrom_getsense(NULL);
		return;
	}
	outsw(GDROM_DATA_REG, cmd, 6);
}