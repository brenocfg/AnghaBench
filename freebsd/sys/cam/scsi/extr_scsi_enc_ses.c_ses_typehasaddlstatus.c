#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_9__ {TYPE_2__* ses_types; } ;
typedef  TYPE_3__ ses_cache_t ;
typedef  int /*<<< orphan*/  ses_addlstatus_avail_t ;
struct TYPE_11__ {TYPE_3__* private; } ;
struct TYPE_10__ {TYPE_5__ enc_daemon_cache; } ;
typedef  TYPE_4__ enc_softc_t ;
typedef  TYPE_5__ enc_cache_t ;
struct TYPE_8__ {TYPE_1__* hdr; } ;
struct TYPE_7__ {int etype_elm_type; } ;

/* Variables and functions */
#define  ELMTYP_ARRAY_DEV 133 
#define  ELMTYP_DEVICE 132 
#define  ELMTYP_ESCC 131 
#define  ELMTYP_SAS_EXP 130 
#define  ELMTYP_SCSI_INI 129 
#define  ELMTYP_SCSI_TGT 128 
 int /*<<< orphan*/  TYPE_ADDLSTATUS_MANDATORY ; 
 int /*<<< orphan*/  TYPE_ADDLSTATUS_NONE ; 
 int /*<<< orphan*/  TYPE_ADDLSTATUS_OPTIONAL ; 

__attribute__((used)) static ses_addlstatus_avail_t
ses_typehasaddlstatus(enc_softc_t *enc, uint8_t typidx)
{
	enc_cache_t *enc_cache;
	ses_cache_t *ses_cache;

	enc_cache = &enc->enc_daemon_cache;
	ses_cache = enc_cache->private;
	switch(ses_cache->ses_types[typidx].hdr->etype_elm_type) {
	case ELMTYP_DEVICE:
	case ELMTYP_ARRAY_DEV:
	case ELMTYP_SAS_EXP:
		return (TYPE_ADDLSTATUS_MANDATORY);
	case ELMTYP_SCSI_INI:
	case ELMTYP_SCSI_TGT:
	case ELMTYP_ESCC:
		return (TYPE_ADDLSTATUS_OPTIONAL);
	default:
		/* No additional status information available. */
		break;
	}
	return (TYPE_ADDLSTATUS_NONE);
}