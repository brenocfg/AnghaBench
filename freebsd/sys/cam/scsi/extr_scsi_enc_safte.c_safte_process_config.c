#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  union ccb {int dummy; } ccb ;
typedef  int uint8_t ;
struct scfg {int Nfans; int Npwr; int Nslots; int DoorLock; int Ntherm; int Nspkrs; int Ntstats; int pwroff; int slotoff; } ;
struct enc_fsm_state {int dummy; } ;
struct TYPE_8__ {int nelms; TYPE_4__* elm_map; } ;
struct TYPE_9__ {TYPE_1__ enc_cache; struct scfg* enc_private; } ;
typedef  TYPE_2__ enc_softc_t ;
typedef  int /*<<< orphan*/  enc_element_t ;
struct TYPE_10__ {void* elm_type; } ;

/* Variables and functions */
 int EIO ; 
 void* ELMTYP_ALARM ; 
 void* ELMTYP_ARRAY_DEV ; 
 void* ELMTYP_DEVICE ; 
 void* ELMTYP_DOORLOCK ; 
 void* ELMTYP_FAN ; 
 void* ELMTYP_POWER ; 
 void* ELMTYP_THERM ; 
 int /*<<< orphan*/  ENC_FREE_AND_NULL (TYPE_4__*) ; 
 int /*<<< orphan*/  ENC_VLOG (TYPE_2__*,char*,int,...) ; 
 int ENXIO ; 
 int /*<<< orphan*/  M_SCSIENC ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  SAFTE_UPDATE_READENCSTATUS ; 
 int /*<<< orphan*/  SAFTE_UPDATE_READGFLAGS ; 
 int /*<<< orphan*/  SAFTE_UPDATE_READSLOTSTATUS ; 
 scalar_t__ emulate_array_devices ; 
 int /*<<< orphan*/  enc_update_request (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
safte_process_config(enc_softc_t *enc, struct enc_fsm_state *state,
    union ccb *ccb, uint8_t **bufp, int error, int xfer_len)
{
	struct scfg *cfg;
	uint8_t *buf = *bufp;
	int i, r;

	cfg = enc->enc_private;
	if (cfg == NULL)
		return (ENXIO);
	if (error != 0)
		return (error);
	if (xfer_len < 6) {
		ENC_VLOG(enc, "too little data (%d) for configuration\n",
		    xfer_len);
		return (EIO);
	}
	cfg->Nfans = buf[0];
	cfg->Npwr = buf[1];
	cfg->Nslots = buf[2];
	cfg->DoorLock = buf[3];
	cfg->Ntherm = buf[4];
	cfg->Nspkrs = buf[5];
	if (xfer_len >= 7)
		cfg->Ntstats = buf[6] & 0x0f;
	else
		cfg->Ntstats = 0;
	ENC_VLOG(enc, "Nfans %d Npwr %d Nslots %d Lck %d Ntherm %d Nspkrs %d "
	    "Ntstats %d\n",
	    cfg->Nfans, cfg->Npwr, cfg->Nslots, cfg->DoorLock, cfg->Ntherm,
	    cfg->Nspkrs, cfg->Ntstats);

	enc->enc_cache.nelms = cfg->Nfans + cfg->Npwr + cfg->Nslots +
	    cfg->DoorLock + cfg->Ntherm + cfg->Nspkrs + cfg->Ntstats + 1;
	ENC_FREE_AND_NULL(enc->enc_cache.elm_map);
	enc->enc_cache.elm_map =
	    malloc(enc->enc_cache.nelms * sizeof(enc_element_t),
	    M_SCSIENC, M_WAITOK|M_ZERO);

	r = 0;
	/*
	 * Note that this is all arranged for the convenience
	 * in later fetches of status.
	 */
	for (i = 0; i < cfg->Nfans; i++)
		enc->enc_cache.elm_map[r++].elm_type = ELMTYP_FAN;
	cfg->pwroff = (uint8_t) r;
	for (i = 0; i < cfg->Npwr; i++)
		enc->enc_cache.elm_map[r++].elm_type = ELMTYP_POWER;
	for (i = 0; i < cfg->DoorLock; i++)
		enc->enc_cache.elm_map[r++].elm_type = ELMTYP_DOORLOCK;
	if (cfg->Nspkrs > 0)
		enc->enc_cache.elm_map[r++].elm_type = ELMTYP_ALARM;
	for (i = 0; i < cfg->Ntherm; i++)
		enc->enc_cache.elm_map[r++].elm_type = ELMTYP_THERM;
	for (i = 0; i <= cfg->Ntstats; i++)
		enc->enc_cache.elm_map[r++].elm_type = ELMTYP_THERM;
	cfg->slotoff = (uint8_t) r;
	for (i = 0; i < cfg->Nslots; i++)
		enc->enc_cache.elm_map[r++].elm_type =
		    emulate_array_devices ? ELMTYP_ARRAY_DEV :
		     ELMTYP_DEVICE;

	enc_update_request(enc, SAFTE_UPDATE_READGFLAGS);
	enc_update_request(enc, SAFTE_UPDATE_READENCSTATUS);
	enc_update_request(enc, SAFTE_UPDATE_READSLOTSTATUS);

	return (0);
}