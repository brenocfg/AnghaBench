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
typedef  int u8 ;
struct ata_taskfile {int protocol; int flags; int ctl; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
typedef  scalar_t__ __le32 ;

/* Variables and functions */
 int ATA_DEV1 ; 
 int ATA_DEVICE_OBS ; 
#define  ATA_PROT_DMA 129 
#define  ATA_PROT_NODATA 128 
 int ATA_REG_DEVICE ; 
 int ATA_TFLAG_WRITE ; 
 int /*<<< orphan*/  BUG () ; 
 int PDC_PKT_CLEAR_BSY ; 
 int /*<<< orphan*/  PDC_PKT_NODATA ; 
 int /*<<< orphan*/  PDC_PKT_READ ; 
 int PDC_REG_DEVCTL ; 
 scalar_t__ cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned int pdc_pkt_header(struct ata_taskfile *tf,
					  dma_addr_t sg_table,
					  unsigned int devno, u8 *buf)
{
	u8 dev_reg;
	__le32 *buf32 = (__le32 *) buf;

	/* set control bits (byte 0), zero delay seq id (byte 3),
	 * and seq id (byte 2)
	 */
	switch (tf->protocol) {
	case ATA_PROT_DMA:
		if (!(tf->flags & ATA_TFLAG_WRITE))
			buf32[0] = cpu_to_le32(PDC_PKT_READ);
		else
			buf32[0] = 0;
		break;

	case ATA_PROT_NODATA:
		buf32[0] = cpu_to_le32(PDC_PKT_NODATA);
		break;

	default:
		BUG();
		break;
	}

	buf32[1] = cpu_to_le32(sg_table);	/* S/G table addr */
	buf32[2] = 0;				/* no next-packet */

	if (devno == 0)
		dev_reg = ATA_DEVICE_OBS;
	else
		dev_reg = ATA_DEVICE_OBS | ATA_DEV1;

	/* select device */
	buf[12] = (1 << 5) | PDC_PKT_CLEAR_BSY | ATA_REG_DEVICE;
	buf[13] = dev_reg;

	/* device control register */
	buf[14] = (1 << 5) | PDC_REG_DEVCTL;
	buf[15] = tf->ctl;

	return 16; 	/* offset of next byte */
}