#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  union ccb {int dummy; } ccb ;
typedef  int uint8_t ;
struct scfg {int slot_status; int slotoff; int Nslots; int enc_status; int adm_status; } ;
struct enc_fsm_state {int dummy; } ;
struct TYPE_7__ {int enc_status; TYPE_1__* elm_map; } ;
struct TYPE_6__ {struct scfg* enc_private; TYPE_3__ enc_cache; } ;
typedef  TYPE_2__ enc_softc_t ;
typedef  TYPE_3__ enc_cache_t ;
struct TYPE_5__ {scalar_t__ elm_type; int* encstat; int svalid; } ;

/* Variables and functions */
 scalar_t__ ELMTYP_ARRAY_DEV ; 
 int ENXIO ; 
 int /*<<< orphan*/  SAFT_BAIL (int,int) ; 
 int SESCTL_DEVOFF ; 
 int SESCTL_PRDFAIL ; 
 int SESCTL_RQSFLT ; 
 int SESCTL_RQSID ; 
 int SESCTL_RQSINS ; 
 int SESCTL_RQSRMV ; 
 int SES_ENCSTAT_CRITICAL ; 
 int SES_ENCSTAT_NONCRITICAL ; 
 int SES_OBJSTAT_CRIT ; 
 int SES_OBJSTAT_NONCRIT ; 
 int SES_OBJSTAT_NOTINSTALLED ; 
 int SES_OBJSTAT_OK ; 

__attribute__((used)) static int
safte_process_slotstatus(enc_softc_t *enc, struct enc_fsm_state *state,
    union ccb *ccb, uint8_t **bufp, int error, int xfer_len)
{
	struct scfg *cfg;
	uint8_t *buf = *bufp;
	enc_cache_t *cache = &enc->enc_cache;
	int oid, r, i;

	cfg = enc->enc_private;
	if (cfg == NULL)
		return (ENXIO);
	if (error != 0)
		return (error);
	cfg->slot_status = 0;
	oid = cfg->slotoff;
	for (r = i = 0; i < cfg->Nslots; i++, r += 4) {
		SAFT_BAIL(r+3, xfer_len);
		if (cache->elm_map[oid].elm_type == ELMTYP_ARRAY_DEV)
			cache->elm_map[oid].encstat[1] = 0;
		cache->elm_map[oid].encstat[2] &= SESCTL_RQSID;
		cache->elm_map[oid].encstat[3] = 0;
		if ((buf[r+3] & 0x01) == 0) {	/* no device */
			cache->elm_map[oid].encstat[0] = SES_OBJSTAT_NOTINSTALLED;
		} else if (buf[r+0] & 0x02) {
			cache->elm_map[oid].encstat[0] = SES_OBJSTAT_CRIT;
			cfg->slot_status |= SES_ENCSTAT_CRITICAL;
		} else if (buf[r+0] & 0x40) {
			cache->elm_map[oid].encstat[0] = SES_OBJSTAT_NONCRIT;
			cfg->slot_status |= SES_ENCSTAT_NONCRITICAL;
		} else {
			cache->elm_map[oid].encstat[0] = SES_OBJSTAT_OK;
		}
		if (buf[r+3] & 0x2) {
			if (buf[r+3] & 0x01)
				cache->elm_map[oid].encstat[2] |= SESCTL_RQSRMV;
			else
				cache->elm_map[oid].encstat[2] |= SESCTL_RQSINS;
		}
		if ((buf[r+3] & 0x04) == 0)
			cache->elm_map[oid].encstat[3] |= SESCTL_DEVOFF;
		if (buf[r+0] & 0x02)
			cache->elm_map[oid].encstat[3] |= SESCTL_RQSFLT;
		if (buf[r+0] & 0x40)
			cache->elm_map[oid].encstat[0] |= SESCTL_PRDFAIL;
		if (cache->elm_map[oid].elm_type == ELMTYP_ARRAY_DEV) {
			if (buf[r+0] & 0x01)
				cache->elm_map[oid].encstat[1] |= 0x80;
			if (buf[r+0] & 0x04)
				cache->elm_map[oid].encstat[1] |= 0x02;
			if (buf[r+0] & 0x08)
				cache->elm_map[oid].encstat[1] |= 0x04;
			if (buf[r+0] & 0x10)
				cache->elm_map[oid].encstat[1] |= 0x08;
			if (buf[r+0] & 0x20)
				cache->elm_map[oid].encstat[1] |= 0x10;
			if (buf[r+1] & 0x01)
				cache->elm_map[oid].encstat[1] |= 0x20;
			if (buf[r+1] & 0x02)
				cache->elm_map[oid].encstat[1] |= 0x01;
		}
		cache->elm_map[oid++].svalid = 1;
	}

	cache->enc_status =
	    cfg->enc_status | cfg->slot_status | cfg->adm_status;
	return (0);
}