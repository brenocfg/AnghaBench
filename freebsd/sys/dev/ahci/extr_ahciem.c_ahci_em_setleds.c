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
struct ahci_enclosure {int** status; int /*<<< orphan*/  r_memc; int /*<<< orphan*/  r_memt; } ;
typedef  int int16_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int AHCI_EM_RST ; 
 int AHCI_EM_TM ; 
 int ATA_INL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATA_OUTL (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int SESCTL_RQSACT ; 
 int SESCTL_RQSFLT ; 
 int SESCTL_RQSID ; 
 int SESCTL_RQSRR ; 
 struct ahci_enclosure* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
ahci_em_setleds(device_t dev, int c)
{
	struct ahci_enclosure *enc;
	int timeout;
	int16_t val;

	enc = device_get_softc(dev);

	val = 0;
	if (enc->status[c][2] & SESCTL_RQSACT)		/* Activity */
		val |= (1 << 0);
	if (enc->status[c][1] & SESCTL_RQSRR)		/* Rebuild */
		val |= (1 << 6) | (1 << 3);
	else if (enc->status[c][2] & SESCTL_RQSID)	/* Identification */
		val |= (1 << 3);
	else if (enc->status[c][3] & SESCTL_RQSFLT)	/* Fault */
		val |= (1 << 6);

	timeout = 10000;
	while (ATA_INL(enc->r_memc, 0) & (AHCI_EM_TM | AHCI_EM_RST) &&
	    --timeout > 0)
		DELAY(100);
	if (timeout == 0)
		device_printf(dev, "Transmit timeout\n");
	ATA_OUTL(enc->r_memt, 0, (1 << 8) | (0 << 16) | (0 << 24));
	ATA_OUTL(enc->r_memt, 4, c | (0 << 8) | (val << 16));
	ATA_OUTL(enc->r_memc, 0, AHCI_EM_TM);
}