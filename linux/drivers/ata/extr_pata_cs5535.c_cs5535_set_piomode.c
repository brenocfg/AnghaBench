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
typedef  int u32 ;
typedef  int u16 ;
struct ata_port {int dummy; } ;
struct ata_device {int pio_mode; int devno; } ;

/* Variables and functions */
 scalar_t__ ATAC_CH0D0_DMA ; 
 scalar_t__ ATAC_CH0D0_PIO ; 
 int XFER_PIO_0 ; 
 struct ata_device* ata_dev_pair (struct ata_device*) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  rdmsr (scalar_t__,int,int) ; 
 int /*<<< orphan*/  wrmsr (scalar_t__,int const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cs5535_set_piomode(struct ata_port *ap, struct ata_device *adev)
{
	static const u16 pio_timings[5] = {
		0xF7F4, 0xF173, 0x8141, 0x5131, 0x1131
	};
	static const u16 pio_cmd_timings[5] = {
		0xF7F4, 0x53F3, 0x13F1, 0x5131, 0x1131
	};
	u32 reg, dummy;
	struct ata_device *pair = ata_dev_pair(adev);

	int mode = adev->pio_mode - XFER_PIO_0;
	int cmdmode = mode;

	/* Command timing has to be for the lowest of the pair of devices */
	if (pair) {
		int pairmode = pair->pio_mode - XFER_PIO_0;
		cmdmode = min(mode, pairmode);
		/* Write the other drive timing register if it changed */
		if (cmdmode < pairmode)
			wrmsr(ATAC_CH0D0_PIO + 2 * pair->devno,
				pio_cmd_timings[cmdmode] << 16 | pio_timings[pairmode], 0);
	}
	/* Write the drive timing register */
	wrmsr(ATAC_CH0D0_PIO + 2 * adev->devno,
		pio_cmd_timings[cmdmode] << 16 | pio_timings[mode], 0);

	/* Set the PIO "format 1" bit in the DMA timing register */
	rdmsr(ATAC_CH0D0_DMA + 2 * adev->devno, reg, dummy);
	wrmsr(ATAC_CH0D0_DMA + 2 * adev->devno, reg | 0x80000000UL, 0);
}