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
struct ahci_port {int* err_cfis; int ci; int tfd; } ;
typedef  int /*<<< orphan*/  fis ;

/* Variables and functions */
 int ATA_S_ERROR ; 
 int FIS_TYPE_REGD2H ; 
 int /*<<< orphan*/  ahci_write_fis (struct ahci_port*,int,int*) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ahci_write_fis_d2h(struct ahci_port *p, int slot, uint8_t *cfis, uint32_t tfd)
{
	uint8_t fis[20];
	uint8_t error;

	error = (tfd >> 8) & 0xff;
	memset(fis, 0, sizeof(fis));
	fis[0] = FIS_TYPE_REGD2H;
	fis[1] = (1 << 6);
	fis[2] = tfd & 0xff;
	fis[3] = error;
	fis[4] = cfis[4];
	fis[5] = cfis[5];
	fis[6] = cfis[6];
	fis[7] = cfis[7];
	fis[8] = cfis[8];
	fis[9] = cfis[9];
	fis[10] = cfis[10];
	fis[11] = cfis[11];
	fis[12] = cfis[12];
	fis[13] = cfis[13];
	if (fis[2] & ATA_S_ERROR) {
		p->err_cfis[0] = 0x80;
		p->err_cfis[2] = tfd & 0xff;
		p->err_cfis[3] = error;
		memcpy(&p->err_cfis[4], cfis + 4, 16);
	} else
		p->ci &= ~(1 << slot);
	p->tfd = tfd;
	ahci_write_fis(p, FIS_TYPE_REGD2H, fis);
}