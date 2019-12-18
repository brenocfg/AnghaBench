#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  status; } ;
struct TYPE_4__ {int flags; int control; } ;
struct ata_res {int lba_high; int lba_mid; } ;
struct TYPE_5__ {TYPE_1__ cmd; struct ata_res res; } ;
union ccb {TYPE_3__ ccb_h; TYPE_2__ ataio; } ;
struct ahci_enclosure {int capsem; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int AHCI_EM_LED ; 
 int ATA_A_RESET ; 
 int CAM_ATAIO_CONTROL ; 
 int /*<<< orphan*/  CAM_REQ_CMP ; 
 int /*<<< orphan*/  CAM_REQ_INVALID ; 
 int /*<<< orphan*/  ahci_em_emulate_ses_on_led (int /*<<< orphan*/ ,union ccb*) ; 
 int /*<<< orphan*/  bzero (struct ata_res*,int) ; 
 struct ahci_enclosure* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 

__attribute__((used)) static void
ahci_em_begin_transaction(device_t dev, union ccb *ccb)
{
	struct ahci_enclosure *enc;
	struct ata_res *res;

	enc = device_get_softc(dev);
	res = &ccb->ataio.res;
	bzero(res, sizeof(*res));
	if ((ccb->ataio.cmd.flags & CAM_ATAIO_CONTROL) &&
	    (ccb->ataio.cmd.control & ATA_A_RESET)) {
		res->lba_high = 0xc3;
		res->lba_mid = 0x3c;
		ccb->ccb_h.status = CAM_REQ_CMP;
		xpt_done(ccb);
		return;
	}

	if (enc->capsem & AHCI_EM_LED) {
		ahci_em_emulate_ses_on_led(dev, ccb);
		return;
	} else
		device_printf(dev, "Unsupported enclosure interface\n");

	ccb->ccb_h.status = CAM_REQ_INVALID;
	xpt_done(ccb);
}