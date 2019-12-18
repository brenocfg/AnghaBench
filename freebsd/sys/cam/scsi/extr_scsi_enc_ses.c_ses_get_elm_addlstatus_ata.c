#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct ses_elm_ata_hdr {int dummy; } ;
struct TYPE_12__ {struct ses_elm_ata_hdr* ata; } ;
struct TYPE_13__ {TYPE_3__ proto_hdr; } ;
struct TYPE_15__ {TYPE_4__ addl; } ;
typedef  TYPE_6__ ses_element_t ;
struct TYPE_16__ {TYPE_2__* ses_types; } ;
typedef  TYPE_7__ ses_cache_t ;
typedef  int /*<<< orphan*/  enc_softc_t ;
struct TYPE_17__ {TYPE_5__* elm_map; TYPE_7__* private; } ;
typedef  TYPE_8__ enc_cache_t ;
struct TYPE_14__ {scalar_t__ elm_private; } ;
struct TYPE_11__ {TYPE_1__* hdr; } ;
struct TYPE_10__ {int etype_elm_type; } ;

/* Variables and functions */
 int EIO ; 
#define  ELMTYP_ARRAY_DEV 129 
#define  ELMTYP_DEVICE 128 
 int /*<<< orphan*/  ENC_VLOG (int /*<<< orphan*/ *,char*,int,int) ; 
 int ENODEV ; 

__attribute__((used)) static int
ses_get_elm_addlstatus_ata(enc_softc_t *enc, enc_cache_t *enc_cache,
			   uint8_t *buf, int bufsiz, int eip, int tidx,
			   int nobj)
{
	int err;
	ses_cache_t *ses_cache;

	if (bufsiz < sizeof(struct ses_elm_ata_hdr)) {
		err = EIO;
		goto out;
	}

	ses_cache = enc_cache->private;
	switch(ses_cache->ses_types[tidx].hdr->etype_elm_type) {
	case ELMTYP_DEVICE:
	case ELMTYP_ARRAY_DEV:
		break;
	default:
		ENC_VLOG(enc, "Element %d has Additional Status, "
		    "invalid for SES element type 0x%x\n", nobj,
		    ses_cache->ses_types[tidx].hdr->etype_elm_type);
		err = ENODEV;
		goto out;
	}

	((ses_element_t *)enc_cache->elm_map[nobj].elm_private)
	    ->addl.proto_hdr.ata = (struct ses_elm_ata_hdr *)buf;
	err = 0;

out:
	return (err);
}