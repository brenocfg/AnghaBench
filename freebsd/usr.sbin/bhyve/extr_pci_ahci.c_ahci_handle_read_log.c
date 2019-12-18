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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct ahci_port {int /*<<< orphan*/  bctx; int /*<<< orphan*/  err_cfis; scalar_t__ atapi; scalar_t__ cmd_lst; } ;
struct ahci_cmd_hdr {scalar_t__ prdtl; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int AHCI_CL_SIZE ; 
 int ATA_E_ABORT ; 
 int ATA_READ_LOG_EXT ; 
 int ATA_S_DSC ; 
 int ATA_S_ERROR ; 
 int ATA_S_READY ; 
 int /*<<< orphan*/  ahci_checksum (int*,int) ; 
 int /*<<< orphan*/  ahci_write_fis_d2h (struct ahci_port*,int,int*,int) ; 
 int /*<<< orphan*/  ahci_write_fis_piosetup (struct ahci_port*) ; 
 scalar_t__ blockif_candelete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blockif_is_ro (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_prdt (struct ahci_port*,int,int*,void*,int) ; 

__attribute__((used)) static void
ahci_handle_read_log(struct ahci_port *p, int slot, uint8_t *cfis)
{
	struct ahci_cmd_hdr *hdr;
	uint32_t buf[128];
	uint8_t *buf8 = (uint8_t *)buf;
	uint16_t *buf16 = (uint16_t *)buf;

	hdr = (struct ahci_cmd_hdr *)(p->cmd_lst + slot * AHCI_CL_SIZE);
	if (p->atapi || hdr->prdtl == 0 || cfis[5] != 0 ||
	    cfis[9] != 0 || cfis[12] != 1 || cfis[13] != 0) {
		ahci_write_fis_d2h(p, slot, cfis,
		    (ATA_E_ABORT << 8) | ATA_S_READY | ATA_S_ERROR);
		return;
	}

	memset(buf, 0, sizeof(buf));
	if (cfis[4] == 0x00) {	/* Log directory */
		buf16[0x00] = 1; /* Version -- 1 */
		buf16[0x10] = 1; /* NCQ Command Error Log -- 1 page */
		buf16[0x13] = 1; /* SATA NCQ Send and Receive Log -- 1 page */
	} else if (cfis[4] == 0x10) {	/* NCQ Command Error Log */
		memcpy(buf8, p->err_cfis, sizeof(p->err_cfis));
		ahci_checksum(buf8, sizeof(buf));
	} else if (cfis[4] == 0x13) {	/* SATA NCQ Send and Receive Log */
		if (blockif_candelete(p->bctx) && !blockif_is_ro(p->bctx)) {
			buf[0x00] = 1;	/* SFQ DSM supported */
			buf[0x01] = 1;	/* SFQ DSM TRIM supported */
		}
	} else {
		ahci_write_fis_d2h(p, slot, cfis,
		    (ATA_E_ABORT << 8) | ATA_S_READY | ATA_S_ERROR);
		return;
	}

	if (cfis[2] == ATA_READ_LOG_EXT)
		ahci_write_fis_piosetup(p);
	write_prdt(p, slot, cfis, (void *)buf, sizeof(buf));
	ahci_write_fis_d2h(p, slot, cfis, ATA_S_DSC | ATA_S_READY);
}