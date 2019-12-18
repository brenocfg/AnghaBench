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
struct tpm_chip {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  RDFIFO ; 
 int /*<<< orphan*/  STAT ; 
 int STAT_RDA ; 
 int TPM_MAX_TRIES ; 
 int /*<<< orphan*/  WRFIFO ; 
 int tpm_data_in (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int empty_fifo(struct tpm_chip *chip, int clear_wrfifo)
{
	int status;
	int check = 0;
	int i;

	if (clear_wrfifo) {
		for (i = 0; i < 4096; i++) {
			status = tpm_data_in(WRFIFO);
			if (status == 0xff) {
				if (check == 5)
					break;
				else
					check++;
			}
		}
	}
	/* Note: The values which are currently in the FIFO of the TPM
	   are thrown away since there is no usage for them. Usually,
	   this has nothing to say, since the TPM will give its answer
	   immediately or will be aborted anyway, so the data here is
	   usually garbage and useless.
	   We have to clean this, because the next communication with
	   the TPM would be rubbish, if there is still some old data
	   in the Read FIFO.
	 */
	i = 0;
	do {
		status = tpm_data_in(RDFIFO);
		status = tpm_data_in(STAT);
		i++;
		if (i == TPM_MAX_TRIES)
			return -EIO;
	} while ((status & (1 << STAT_RDA)) != 0);
	return 0;
}