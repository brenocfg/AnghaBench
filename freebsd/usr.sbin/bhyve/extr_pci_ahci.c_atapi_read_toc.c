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
typedef  int uint8_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
struct ahci_port {int sense_key; int asc; int /*<<< orphan*/  bctx; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int ATA_I_CMD ; 
 int ATA_I_IN ; 
 void* ATA_SENSE_ILLEGAL_REQUEST ; 
 int ATA_S_DSC ; 
 int ATA_S_ERROR ; 
 int ATA_S_READY ; 
 int /*<<< orphan*/  ahci_write_fis_d2h (struct ahci_port*,int,int*,int) ; 
 int be16dec (int*) ; 
 int /*<<< orphan*/  be16enc (int*,int) ; 
 int /*<<< orphan*/  be32enc (int*,int) ; 
 int blockif_sectsz (int /*<<< orphan*/ ) ; 
 int blockif_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lba_to_msf (int*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_prdt (struct ahci_port*,int,int*,int*,int) ; 

__attribute__((used)) static void
atapi_read_toc(struct ahci_port *p, int slot, uint8_t *cfis)
{
	uint8_t *acmd;
	uint8_t format;
	int len;

	acmd = cfis + 0x40;

	len = be16dec(acmd + 7);
	format = acmd[9] >> 6;
	switch (format) {
	case 0:
	{
		int msf, size;
		uint64_t sectors;
		uint8_t start_track, buf[20], *bp;

		msf = (acmd[1] >> 1) & 1;
		start_track = acmd[6];
		if (start_track > 1 && start_track != 0xaa) {
			uint32_t tfd;
			p->sense_key = ATA_SENSE_ILLEGAL_REQUEST;
			p->asc = 0x24;
			tfd = (p->sense_key << 12) | ATA_S_READY | ATA_S_ERROR;
			cfis[4] = (cfis[4] & ~7) | ATA_I_CMD | ATA_I_IN;
			ahci_write_fis_d2h(p, slot, cfis, tfd);
			return;
		}
		bp = buf + 2;
		*bp++ = 1;
		*bp++ = 1;
		if (start_track <= 1) {
			*bp++ = 0;
			*bp++ = 0x14;
			*bp++ = 1;
			*bp++ = 0;
			if (msf) {
				*bp++ = 0;
				lba_to_msf(bp, 0);
				bp += 3;
			} else {
				*bp++ = 0;
				*bp++ = 0;
				*bp++ = 0;
				*bp++ = 0;
			}
		}
		*bp++ = 0;
		*bp++ = 0x14;
		*bp++ = 0xaa;
		*bp++ = 0;
		sectors = blockif_size(p->bctx) / blockif_sectsz(p->bctx);
		sectors >>= 2;
		if (msf) {
			*bp++ = 0;
			lba_to_msf(bp, sectors);
			bp += 3;
		} else {
			be32enc(bp, sectors);
			bp += 4;
		}
		size = bp - buf;
		be16enc(buf, size - 2);
		if (len > size)
			len = size;
		write_prdt(p, slot, cfis, buf, len);
		cfis[4] = (cfis[4] & ~7) | ATA_I_CMD | ATA_I_IN;
		ahci_write_fis_d2h(p, slot, cfis, ATA_S_READY | ATA_S_DSC);
		break;
	}
	case 1:
	{
		uint8_t buf[12];

		memset(buf, 0, sizeof(buf));
		buf[1] = 0xa;
		buf[2] = 0x1;
		buf[3] = 0x1;
		if (len > sizeof(buf))
			len = sizeof(buf);
		write_prdt(p, slot, cfis, buf, len);
		cfis[4] = (cfis[4] & ~7) | ATA_I_CMD | ATA_I_IN;
		ahci_write_fis_d2h(p, slot, cfis, ATA_S_READY | ATA_S_DSC);
		break;
	}
	case 2:
	{
		int msf, size;
		uint64_t sectors;
		uint8_t *bp, buf[50];

		msf = (acmd[1] >> 1) & 1;
		bp = buf + 2;
		*bp++ = 1;
		*bp++ = 1;

		*bp++ = 1;
		*bp++ = 0x14;
		*bp++ = 0;
		*bp++ = 0xa0;
		*bp++ = 0;
		*bp++ = 0;
		*bp++ = 0;
		*bp++ = 0;
		*bp++ = 1;
		*bp++ = 0;
		*bp++ = 0;

		*bp++ = 1;
		*bp++ = 0x14;
		*bp++ = 0;
		*bp++ = 0xa1;
		*bp++ = 0;
		*bp++ = 0;
		*bp++ = 0;
		*bp++ = 0;
		*bp++ = 1;
		*bp++ = 0;
		*bp++ = 0;

		*bp++ = 1;
		*bp++ = 0x14;
		*bp++ = 0;
		*bp++ = 0xa2;
		*bp++ = 0;
		*bp++ = 0;
		*bp++ = 0;
		sectors = blockif_size(p->bctx) / blockif_sectsz(p->bctx);
		sectors >>= 2;
		if (msf) {
			*bp++ = 0;
			lba_to_msf(bp, sectors);
			bp += 3;
		} else {
			be32enc(bp, sectors);
			bp += 4;
		}

		*bp++ = 1;
		*bp++ = 0x14;
		*bp++ = 0;
		*bp++ = 1;
		*bp++ = 0;
		*bp++ = 0;
		*bp++ = 0;
		if (msf) {
			*bp++ = 0;
			lba_to_msf(bp, 0);
			bp += 3;
		} else {
			*bp++ = 0;
			*bp++ = 0;
			*bp++ = 0;
			*bp++ = 0;
		}

		size = bp - buf;
		be16enc(buf, size - 2);
		if (len > size)
			len = size;
		write_prdt(p, slot, cfis, buf, len);
		cfis[4] = (cfis[4] & ~7) | ATA_I_CMD | ATA_I_IN;
		ahci_write_fis_d2h(p, slot, cfis, ATA_S_READY | ATA_S_DSC);
		break;
	}
	default:
	{
		uint32_t tfd;

		p->sense_key = ATA_SENSE_ILLEGAL_REQUEST;
		p->asc = 0x24;
		tfd = (p->sense_key << 12) | ATA_S_READY | ATA_S_ERROR;
		cfis[4] = (cfis[4] & ~7) | ATA_I_CMD | ATA_I_IN;
		ahci_write_fis_d2h(p, slot, cfis, tfd);
		break;
	}
	}
}