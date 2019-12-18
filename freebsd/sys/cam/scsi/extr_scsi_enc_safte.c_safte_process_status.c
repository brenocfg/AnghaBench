#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  union ccb {int dummy; } ccb ;
typedef  int uint8_t ;
typedef  int uint16_t ;
struct scfg {int enc_status; int Nfans; int flag1; int Ntherm; int Ntstats; int Npwr; int Nslots; int slotoff; int slot_status; int adm_status; scalar_t__ Nspkrs; scalar_t__ DoorLock; } ;
struct enc_fsm_state {int dummy; } ;
struct TYPE_8__ {int enc_status; TYPE_1__* elm_map; } ;
struct TYPE_7__ {TYPE_3__ enc_cache; struct scfg* enc_private; } ;
typedef  TYPE_2__ enc_softc_t ;
typedef  TYPE_3__ enc_cache_t ;
struct TYPE_6__ {int* encstat; int svalid; scalar_t__ elm_type; } ;

/* Variables and functions */
 scalar_t__ ELMTYP_DEVICE ; 
 int /*<<< orphan*/  ENC_VLOG (TYPE_2__*,char*,int,...) ; 
 int ENXIO ; 
 int /*<<< orphan*/  SAFT_BAIL (int,int) ; 
 int SAFT_FLG1_ENCFANFAIL ; 
 int SESCTL_DISABLE ; 
 int SES_ENCSTAT_CRITICAL ; 
 int SES_ENCSTAT_INFO ; 
 int SES_ENCSTAT_NONCRITICAL ; 
 void* SES_OBJSTAT_CRIT ; 
 int SES_OBJSTAT_NONCRIT ; 
 int SES_OBJSTAT_NOTAVAIL ; 
 void* SES_OBJSTAT_NOTINSTALLED ; 
 void* SES_OBJSTAT_OK ; 
 void* SES_OBJSTAT_UNKNOWN ; 
 void* SES_OBJSTAT_UNSUPPORTED ; 

__attribute__((used)) static int
safte_process_status(enc_softc_t *enc, struct enc_fsm_state *state,
    union ccb *ccb, uint8_t **bufp, int error, int xfer_len)
{
	struct scfg *cfg;
	uint8_t *buf = *bufp;
	int oid, r, i, nitems;
	uint16_t tempflags;
	enc_cache_t *cache = &enc->enc_cache;

	cfg = enc->enc_private;
	if (cfg == NULL)
		return (ENXIO);
	if (error != 0)
		return (error);

	oid = r = 0;
	cfg->enc_status = 0;

	for (nitems = i = 0; i < cfg->Nfans; i++) {
		SAFT_BAIL(r, xfer_len);
		/*
		 * 0 = Fan Operational
		 * 1 = Fan is malfunctioning
		 * 2 = Fan is not present
		 * 0x80 = Unknown or Not Reportable Status
		 */
		cache->elm_map[oid].encstat[1] = 0;	/* resvd */
		cache->elm_map[oid].encstat[2] = 0;	/* resvd */
		if (cfg->flag1 & SAFT_FLG1_ENCFANFAIL)
			cache->elm_map[oid].encstat[3] |= 0x40;
		else
			cache->elm_map[oid].encstat[3] &= ~0x40;
		switch ((int)buf[r]) {
		case 0:
			nitems++;
			cache->elm_map[oid].encstat[0] = SES_OBJSTAT_OK;
			if ((cache->elm_map[oid].encstat[3] & 0x37) == 0)
				cache->elm_map[oid].encstat[3] |= 0x27;
			break;

		case 1:
			cache->elm_map[oid].encstat[0] =
			    SES_OBJSTAT_CRIT;
			/*
			 * FAIL and FAN STOPPED synthesized
			 */
			cache->elm_map[oid].encstat[3] |= 0x10;
			cache->elm_map[oid].encstat[3] &= ~0x07;
			/*
			 * Enclosure marked with CRITICAL error
			 * if only one fan or no thermometers,
			 * else the NONCRITICAL error is set.
			 */
			if (cfg->Nfans == 1 || (cfg->Ntherm + cfg->Ntstats) == 0)
				cfg->enc_status |= SES_ENCSTAT_CRITICAL;
			else
				cfg->enc_status |= SES_ENCSTAT_NONCRITICAL;
			break;
		case 2:
			cache->elm_map[oid].encstat[0] =
			    SES_OBJSTAT_NOTINSTALLED;
			cache->elm_map[oid].encstat[3] |= 0x10;
			cache->elm_map[oid].encstat[3] &= ~0x07;
			/*
			 * Enclosure marked with CRITICAL error
			 * if only one fan or no thermometers,
			 * else the NONCRITICAL error is set.
			 */
			if (cfg->Nfans == 1)
				cfg->enc_status |= SES_ENCSTAT_CRITICAL;
			else
				cfg->enc_status |= SES_ENCSTAT_NONCRITICAL;
			break;
		case 0x80:
			cache->elm_map[oid].encstat[0] = SES_OBJSTAT_UNKNOWN;
			cache->elm_map[oid].encstat[3] = 0;
			cfg->enc_status |= SES_ENCSTAT_INFO;
			break;
		default:
			cache->elm_map[oid].encstat[0] = SES_OBJSTAT_UNSUPPORTED;
			ENC_VLOG(enc, "Unknown fan%d status 0x%x\n", i,
			    buf[r] & 0xff);
			break;
		}
		cache->elm_map[oid++].svalid = 1;
		r++;
	}

	/*
	 * No matter how you cut it, no cooling elements when there
	 * should be some there is critical.
	 */
	if (cfg->Nfans && nitems == 0)
		cfg->enc_status |= SES_ENCSTAT_CRITICAL;

	for (i = 0; i < cfg->Npwr; i++) {
		SAFT_BAIL(r, xfer_len);
		cache->elm_map[oid].encstat[0] = SES_OBJSTAT_UNKNOWN;
		cache->elm_map[oid].encstat[1] = 0;	/* resvd */
		cache->elm_map[oid].encstat[2] = 0;	/* resvd */
		cache->elm_map[oid].encstat[3] = 0x20;	/* requested on */
		switch (buf[r]) {
		case 0x00:	/* pws operational and on */
			cache->elm_map[oid].encstat[0] = SES_OBJSTAT_OK;
			break;
		case 0x01:	/* pws operational and off */
			cache->elm_map[oid].encstat[0] = SES_OBJSTAT_OK;
			cache->elm_map[oid].encstat[3] = 0x10;
			cfg->enc_status |= SES_ENCSTAT_INFO;
			break;
		case 0x10:	/* pws is malfunctioning and commanded on */
			cache->elm_map[oid].encstat[0] = SES_OBJSTAT_CRIT;
			cache->elm_map[oid].encstat[3] = 0x61;
			cfg->enc_status |= SES_ENCSTAT_NONCRITICAL;
			break;

		case 0x11:	/* pws is malfunctioning and commanded off */
			cache->elm_map[oid].encstat[0] = SES_OBJSTAT_NONCRIT;
			cache->elm_map[oid].encstat[3] = 0x51;
			cfg->enc_status |= SES_ENCSTAT_NONCRITICAL;
			break;
		case 0x20:	/* pws is not present */
			cache->elm_map[oid].encstat[0] =
			    SES_OBJSTAT_NOTINSTALLED;
			cache->elm_map[oid].encstat[3] = 0;
			cfg->enc_status |= SES_ENCSTAT_INFO;
			break;
		case 0x21:	/* pws is present */
			/*
			 * This is for enclosures that cannot tell whether the
			 * device is on or malfunctioning, but know that it is
			 * present. Just fall through.
			 */
			/* FALLTHROUGH */
		case 0x80:	/* Unknown or Not Reportable Status */
			cache->elm_map[oid].encstat[0] = SES_OBJSTAT_UNKNOWN;
			cache->elm_map[oid].encstat[3] = 0;
			cfg->enc_status |= SES_ENCSTAT_INFO;
			break;
		default:
			ENC_VLOG(enc, "unknown power supply %d status (0x%x)\n",
			    i, buf[r] & 0xff);
			break;
		}
		enc->enc_cache.elm_map[oid++].svalid = 1;
		r++;
	}

	/*
	 * Copy Slot SCSI IDs
	 */
	for (i = 0; i < cfg->Nslots; i++) {
		SAFT_BAIL(r, xfer_len);
		if (cache->elm_map[cfg->slotoff + i].elm_type == ELMTYP_DEVICE)
			cache->elm_map[cfg->slotoff + i].encstat[1] = buf[r];
		r++;
	}

	/*
	 * We always have doorlock status, no matter what,
	 * but we only save the status if we have one.
	 */
	SAFT_BAIL(r, xfer_len);
	if (cfg->DoorLock) {
		/*
		 * 0 = Door Locked
		 * 1 = Door Unlocked, or no Lock Installed
		 * 0x80 = Unknown or Not Reportable Status
		 */
		cache->elm_map[oid].encstat[1] = 0;
		cache->elm_map[oid].encstat[2] = 0;
		switch (buf[r]) {
		case 0:
			cache->elm_map[oid].encstat[0] = SES_OBJSTAT_OK;
			cache->elm_map[oid].encstat[3] = 0;
			break;
		case 1:
			cache->elm_map[oid].encstat[0] = SES_OBJSTAT_OK;
			cache->elm_map[oid].encstat[3] = 1;
			break;
		case 0x80:
			cache->elm_map[oid].encstat[0] = SES_OBJSTAT_UNKNOWN;
			cache->elm_map[oid].encstat[3] = 0;
			cfg->enc_status |= SES_ENCSTAT_INFO;
			break;
		default:
			cache->elm_map[oid].encstat[0] =
			    SES_OBJSTAT_UNSUPPORTED;
			ENC_VLOG(enc, "unknown lock status 0x%x\n",
			    buf[r] & 0xff);
			break;
		}
		cache->elm_map[oid++].svalid = 1;
	}
	r++;

	/*
	 * We always have speaker status, no matter what,
	 * but we only save the status if we have one.
	 */
	SAFT_BAIL(r, xfer_len);
	if (cfg->Nspkrs) {
		cache->elm_map[oid].encstat[0] = SES_OBJSTAT_OK;
		cache->elm_map[oid].encstat[1] = 0;
		cache->elm_map[oid].encstat[2] = 0;
		if (buf[r] == 0) {
			cache->elm_map[oid].encstat[0] |= SESCTL_DISABLE;
			cache->elm_map[oid].encstat[3] |= 0x40;
		}
		cache->elm_map[oid++].svalid = 1;
	}
	r++;

	/*
	 * Now, for "pseudo" thermometers, we have two bytes
	 * of information in enclosure status- 16 bits. Actually,
	 * the MSB is a single TEMP ALERT flag indicating whether
	 * any other bits are set, but, thanks to fuzzy thinking,
	 * in the SAF-TE spec, this can also be set even if no
	 * other bits are set, thus making this really another
	 * binary temperature sensor.
	 */

	SAFT_BAIL(r + cfg->Ntherm, xfer_len);
	tempflags = buf[r + cfg->Ntherm];
	SAFT_BAIL(r + cfg->Ntherm + 1, xfer_len);
	tempflags |= (tempflags << 8) | buf[r + cfg->Ntherm + 1];

	for (i = 0; i < cfg->Ntherm; i++) {
		SAFT_BAIL(r, xfer_len);
		/*
		 * Status is a range from -10 to 245 deg Celsius,
		 * which we need to normalize to -20 to -245 according
		 * to the latest SCSI spec, which makes little
		 * sense since this would overflow an 8bit value.
		 * Well, still, the base normalization is -20,
		 * not -10, so we have to adjust.
		 *
		 * So what's over and under temperature?
		 * Hmm- we'll state that 'normal' operating
		 * is 10 to 40 deg Celsius.
		 */

		/*
		 * Actually.... All of the units that people out in the world
		 * seem to have do not come even close to setting a value that
		 * complies with this spec.
		 *
		 * The closest explanation I could find was in an
		 * LSI-Logic manual, which seemed to indicate that
		 * this value would be set by whatever the I2C code
		 * would interpolate from the output of an LM75
		 * temperature sensor.
		 *
		 * This means that it is impossible to use the actual
		 * numeric value to predict anything. But we don't want
		 * to lose the value. So, we'll propagate the *uncorrected*
		 * value and set SES_OBJSTAT_NOTAVAIL. We'll depend on the
		 * temperature flags for warnings.
		 */
		if (tempflags & (1 << i)) {
			cache->elm_map[oid].encstat[0] = SES_OBJSTAT_CRIT;
			cfg->enc_status |= SES_ENCSTAT_CRITICAL;
		} else
			cache->elm_map[oid].encstat[0] = SES_OBJSTAT_OK;
		cache->elm_map[oid].encstat[1] = 0;
		cache->elm_map[oid].encstat[2] = buf[r];
		cache->elm_map[oid].encstat[3] = 0;
		cache->elm_map[oid++].svalid = 1;
		r++;
	}

	for (i = 0; i <= cfg->Ntstats; i++) {
		cache->elm_map[oid].encstat[1] = 0;
		if (tempflags & (1 <<
		    ((i == cfg->Ntstats) ? 15 : (cfg->Ntherm + i)))) {
			cache->elm_map[oid].encstat[0] = SES_OBJSTAT_CRIT;
			cache->elm_map[4].encstat[2] = 0xff;
			/*
			 * Set 'over temperature' failure.
			 */
			cache->elm_map[oid].encstat[3] = 8;
			cfg->enc_status |= SES_ENCSTAT_CRITICAL;
		} else {
			/*
			 * We used to say 'not available' and synthesize a
			 * nominal 30 deg (C)- that was wrong. Actually,
			 * Just say 'OK', and use the reserved value of
			 * zero.
			 */
			if ((cfg->Ntherm + cfg->Ntstats) == 0)
				cache->elm_map[oid].encstat[0] =
				    SES_OBJSTAT_NOTAVAIL;
			else
				cache->elm_map[oid].encstat[0] =
				    SES_OBJSTAT_OK;
			cache->elm_map[oid].encstat[2] = 0;
			cache->elm_map[oid].encstat[3] = 0;
		}
		cache->elm_map[oid++].svalid = 1;
	}
	r += 2;

	cache->enc_status =
	    cfg->enc_status | cfg->slot_status | cfg->adm_status;
	return (0);
}