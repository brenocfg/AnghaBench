#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nvme_controller_data {int vid; int ssvid; int rab; int* ieee; int mdts; int ver; int oacs; int acl; int aerl; int npss; int wctemp; int sqes; int cqes; int nn; int fna; TYPE_1__* power_state; scalar_t__ elpe; scalar_t__ lpa; scalar_t__ mic; scalar_t__ fr; scalar_t__ mn; } ;
struct pci_nvme_softc {struct nvme_controller_data ctrldata; } ;
struct TYPE_2__ {int mp; } ;

/* Variables and functions */
 int NVME_CTRLR_DATA_CQES_MAX_SHIFT ; 
 int NVME_CTRLR_DATA_CQES_MIN_SHIFT ; 
 int NVME_CTRLR_DATA_OACS_FORMAT_SHIFT ; 
 int NVME_CTRLR_DATA_SQES_MAX_SHIFT ; 
 int NVME_CTRLR_DATA_SQES_MIN_SHIFT ; 
 int /*<<< orphan*/  cpywithpad (char*,int,char*,char) ; 

__attribute__((used)) static void
pci_nvme_init_ctrldata(struct pci_nvme_softc *sc)
{
	struct nvme_controller_data *cd = &sc->ctrldata;

	cd->vid = 0xFB5D;
	cd->ssvid = 0x0000;

	cpywithpad((char *)cd->mn, sizeof(cd->mn), "bhyve-NVMe", ' ');
	cpywithpad((char *)cd->fr, sizeof(cd->fr), "1.0", ' ');

	/* Num of submission commands that we can handle at a time (2^rab) */
	cd->rab   = 4;

	/* FreeBSD OUI */
	cd->ieee[0] = 0x58;
	cd->ieee[1] = 0x9c;
	cd->ieee[2] = 0xfc;

	cd->mic = 0;

	cd->mdts = 9;	/* max data transfer size (2^mdts * CAP.MPSMIN) */

	cd->ver = 0x00010300;

	cd->oacs = 1 << NVME_CTRLR_DATA_OACS_FORMAT_SHIFT;
	cd->acl = 2;
	cd->aerl = 4;

	cd->lpa = 0;	/* TODO: support some simple things like SMART */
	cd->elpe = 0;	/* max error log page entries */
	cd->npss = 1;	/* number of power states support */

	/* Warning Composite Temperature Threshold */
	cd->wctemp = 0x0157;

	cd->sqes = (6 << NVME_CTRLR_DATA_SQES_MAX_SHIFT) |
	    (6 << NVME_CTRLR_DATA_SQES_MIN_SHIFT);
	cd->cqes = (4 << NVME_CTRLR_DATA_CQES_MAX_SHIFT) |
	    (4 << NVME_CTRLR_DATA_CQES_MIN_SHIFT);
	cd->nn = 1;	/* number of namespaces */

	cd->fna = 0x03;

	cd->power_state[0].mp = 10;
}