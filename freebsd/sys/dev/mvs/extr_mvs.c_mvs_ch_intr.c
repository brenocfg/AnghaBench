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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct mvs_intr_arg {int cause; int /*<<< orphan*/  arg; } ;
struct mvs_channel {scalar_t__ numtslots; scalar_t__ numdslots; int quirks; scalar_t__ numpslots; scalar_t__* numrslotspd; int rslots; int fatalerr; int /*<<< orphan*/  r_mem; TYPE_3__* slot; scalar_t__ fbs_enabled; int /*<<< orphan*/  curr_mode; } ;
typedef  enum mvs_err_type { ____Placeholder_mvs_err_type } mvs_err_type ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_6__ {TYPE_2__* ccb; } ;
struct TYPE_4__ {int target_id; } ;
struct TYPE_5__ {TYPE_1__ ccb_h; } ;

/* Variables and functions */
 int ATA_INL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATA_OUTL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EDMA_IEC ; 
 int EDMA_IE_EDEVCON ; 
 int EDMA_IE_EDEVDIS ; 
 int EDMA_IE_EDEVERR ; 
 int EDMA_IE_ESELFDIS ; 
 int EDMA_IE_ETRANSINT ; 
 int EDMA_IE_SERRINT ; 
 int /*<<< orphan*/  EDMA_S ; 
 int EDMA_S_EDEVQUETAG (int) ; 
 int EDMA_S_EIOID (int) ; 
 int /*<<< orphan*/  MVS_EDMA_UNKNOWN ; 
 int MVS_ERR_INNOCENT ; 
 int MVS_ERR_INVALID ; 
 int MVS_ERR_NCQ ; 
 int MVS_ERR_SATA ; 
 int MVS_ERR_TFE ; 
 int MVS_MAX_SLOTS ; 
 int MVS_Q_GENI ; 
 int MVS_Q_GENII ; 
 int MVS_Q_GENIIE ; 
 int SATA_FISC_FISWAIT4HOSTRDYEN_B1 ; 
 int /*<<< orphan*/  SATA_FISIC ; 
 int /*<<< orphan*/  SATA_SATAITC ; 
 int /*<<< orphan*/  SATA_SE ; 
 int SATA_SE_PHY_CHANGED ; 
 struct mvs_channel* device_get_softc (int /*<<< orphan*/ ) ; 
 int ffs (int) ; 
 int fls (int) ; 
 int /*<<< orphan*/  mvs_crbq_intr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvs_end_transaction (TYPE_3__*,int) ; 
 int /*<<< orphan*/  mvs_legacy_intr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mvs_notify_events (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvs_phy_check_events (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mvs_requeue_frozen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mvs_ch_intr(void *data)
{
	struct mvs_intr_arg *arg = (struct mvs_intr_arg *)data;
	device_t dev = (device_t)arg->arg;
	struct mvs_channel *ch = device_get_softc(dev);
	uint32_t iec, serr = 0, fisic = 0;
	enum mvs_err_type et;
	int i, ccs, port = -1, selfdis = 0;
	int edma = (ch->numtslots != 0 || ch->numdslots != 0);

	/* New item in response queue. */
	if ((arg->cause & 2) && edma)
		mvs_crbq_intr(dev);
	/* Some error or special event. */
	if (arg->cause & 1) {
		iec = ATA_INL(ch->r_mem, EDMA_IEC);
		if (iec & EDMA_IE_SERRINT) {
			serr = ATA_INL(ch->r_mem, SATA_SE);
			ATA_OUTL(ch->r_mem, SATA_SE, serr);
		}
		/* EDMA self-disabled due to error. */
		if (iec & EDMA_IE_ESELFDIS)
			selfdis = 1;
		/* Transport interrupt. */
		if (iec & EDMA_IE_ETRANSINT) {
			/* For Gen-I this bit means self-disable. */
			if (ch->quirks & MVS_Q_GENI)
				selfdis = 1;
			/* For Gen-II this bit means SDB-N. */
			else if (ch->quirks & MVS_Q_GENII)
				fisic = SATA_FISC_FISWAIT4HOSTRDYEN_B1;
			else	/* For Gen-IIe - read FIS interrupt cause. */
				fisic = ATA_INL(ch->r_mem, SATA_FISIC);
		}
		if (selfdis)
			ch->curr_mode = MVS_EDMA_UNKNOWN;
		ATA_OUTL(ch->r_mem, EDMA_IEC, ~iec);
		/* Interface errors or Device error. */
		if (iec & (0xfc1e9000 | EDMA_IE_EDEVERR)) {
			port = -1;
			if (ch->numpslots != 0) {
				ccs = 0;
			} else {
				if (ch->quirks & MVS_Q_GENIIE)
					ccs = EDMA_S_EIOID(ATA_INL(ch->r_mem, EDMA_S));
				else
					ccs = EDMA_S_EDEVQUETAG(ATA_INL(ch->r_mem, EDMA_S));
				/* Check if error is one-PMP-port-specific, */
				if (ch->fbs_enabled) {
					/* Which ports were active. */
					for (i = 0; i < 16; i++) {
						if (ch->numrslotspd[i] == 0)
							continue;
						if (port == -1)
							port = i;
						else if (port != i) {
							port = -2;
							break;
						}
					}
					/* If several ports were active and EDMA still enabled - 
					 * other ports are probably unaffected and may continue.
					 */
					if (port == -2 && !selfdis) {
						uint16_t p = ATA_INL(ch->r_mem, SATA_SATAITC) >> 16;
						port = ffs(p) - 1;
						if (port != (fls(p) - 1))
							port = -2;
					}
				}
			}
			mvs_requeue_frozen(dev);
			for (i = 0; i < MVS_MAX_SLOTS; i++) {
				/* XXX: reqests in loading state. */
				if (((ch->rslots >> i) & 1) == 0)
					continue;
				if (port >= 0 &&
				    ch->slot[i].ccb->ccb_h.target_id != port)
					continue;
				if (iec & EDMA_IE_EDEVERR) { /* Device error. */
				    if (port != -2) {
					if (ch->numtslots == 0) {
						/* Untagged operation. */
						if (i == ccs)
							et = MVS_ERR_TFE;
						else
							et = MVS_ERR_INNOCENT;
					} else {
						/* Tagged operation. */
						et = MVS_ERR_NCQ;
					}
				    } else {
					et = MVS_ERR_TFE;
					ch->fatalerr = 1;
				    }
				} else if (iec & 0xfc1e9000) {
					if (ch->numtslots == 0 &&
					    i != ccs && port != -2)
						et = MVS_ERR_INNOCENT;
					else
						et = MVS_ERR_SATA;
				} else
					et = MVS_ERR_INVALID;
				mvs_end_transaction(&ch->slot[i], et);
			}
		}
		/* Process SDB-N. */
		if (fisic & SATA_FISC_FISWAIT4HOSTRDYEN_B1)
			mvs_notify_events(dev);
		if (fisic)
			ATA_OUTL(ch->r_mem, SATA_FISIC, ~fisic);
		/* Process hot-plug. */
		if ((iec & (EDMA_IE_EDEVDIS | EDMA_IE_EDEVCON)) ||
		    (serr & SATA_SE_PHY_CHANGED))
			mvs_phy_check_events(dev, serr);
	}
	/* Legacy mode device interrupt. */
	if ((arg->cause & 2) && !edma)
		mvs_legacy_intr(dev, arg->cause & 4);
}