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
struct pstore_record {int type; int /*<<< orphan*/  id; int /*<<< orphan*/  compressed; scalar_t__ size; } ;
struct TYPE_5__ {int section_count; int /*<<< orphan*/  record_id; int /*<<< orphan*/  flags; int /*<<< orphan*/  notification_type; int /*<<< orphan*/  creator_id; scalar_t__ record_length; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  validation_bits; void* error_severity; int /*<<< orphan*/  signature_end; int /*<<< orphan*/  revision; int /*<<< orphan*/  signature; } ;
struct TYPE_4__ {int section_offset; void* section_severity; int /*<<< orphan*/  section_type; int /*<<< orphan*/  flags; scalar_t__ validation_bits; int /*<<< orphan*/  revision; scalar_t__ section_length; } ;
struct cper_pstore_record {TYPE_2__ hdr; TYPE_1__ sec_hdr; } ;
struct TYPE_6__ {scalar_t__ buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPER_CREATOR_PSTORE ; 
 int /*<<< orphan*/  CPER_HW_ERROR_FLAGS_PREVERR ; 
 int /*<<< orphan*/  CPER_NOTIFY_MCE ; 
 int /*<<< orphan*/  CPER_RECORD_REV ; 
 int /*<<< orphan*/  CPER_SECTION_TYPE_DMESG ; 
 int /*<<< orphan*/  CPER_SECTION_TYPE_DMESG_Z ; 
 int /*<<< orphan*/  CPER_SECTION_TYPE_MCE ; 
 int /*<<< orphan*/  CPER_SEC_PRIMARY ; 
 int /*<<< orphan*/  CPER_SEC_REV ; 
 void* CPER_SEV_FATAL ; 
 int /*<<< orphan*/  CPER_SIG_END ; 
 int /*<<< orphan*/  CPER_SIG_RECORD ; 
 int /*<<< orphan*/  CPER_SIG_SIZE ; 
 int /*<<< orphan*/  CPER_VALID_TIMESTAMP ; 
 int EINVAL ; 
#define  PSTORE_TYPE_DMESG 129 
#define  PSTORE_TYPE_MCE 128 
 int /*<<< orphan*/  cper_next_record_id () ; 
 TYPE_3__ erst_info ; 
 int erst_write (TYPE_2__*) ; 
 int /*<<< orphan*/  ktime_get_real_seconds () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct cper_pstore_record*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int erst_writer(struct pstore_record *record)
{
	struct cper_pstore_record *rcd = (struct cper_pstore_record *)
					(erst_info.buf - sizeof(*rcd));
	int ret;

	memset(rcd, 0, sizeof(*rcd));
	memcpy(rcd->hdr.signature, CPER_SIG_RECORD, CPER_SIG_SIZE);
	rcd->hdr.revision = CPER_RECORD_REV;
	rcd->hdr.signature_end = CPER_SIG_END;
	rcd->hdr.section_count = 1;
	rcd->hdr.error_severity = CPER_SEV_FATAL;
	/* timestamp valid. platform_id, partition_id are invalid */
	rcd->hdr.validation_bits = CPER_VALID_TIMESTAMP;
	rcd->hdr.timestamp = ktime_get_real_seconds();
	rcd->hdr.record_length = sizeof(*rcd) + record->size;
	rcd->hdr.creator_id = CPER_CREATOR_PSTORE;
	rcd->hdr.notification_type = CPER_NOTIFY_MCE;
	rcd->hdr.record_id = cper_next_record_id();
	rcd->hdr.flags = CPER_HW_ERROR_FLAGS_PREVERR;

	rcd->sec_hdr.section_offset = sizeof(*rcd);
	rcd->sec_hdr.section_length = record->size;
	rcd->sec_hdr.revision = CPER_SEC_REV;
	/* fru_id and fru_text is invalid */
	rcd->sec_hdr.validation_bits = 0;
	rcd->sec_hdr.flags = CPER_SEC_PRIMARY;
	switch (record->type) {
	case PSTORE_TYPE_DMESG:
		if (record->compressed)
			rcd->sec_hdr.section_type = CPER_SECTION_TYPE_DMESG_Z;
		else
			rcd->sec_hdr.section_type = CPER_SECTION_TYPE_DMESG;
		break;
	case PSTORE_TYPE_MCE:
		rcd->sec_hdr.section_type = CPER_SECTION_TYPE_MCE;
		break;
	default:
		return -EINVAL;
	}
	rcd->sec_hdr.section_severity = CPER_SEV_FATAL;

	ret = erst_write(&rcd->hdr);
	record->id = rcd->hdr.record_id;

	return ret;
}