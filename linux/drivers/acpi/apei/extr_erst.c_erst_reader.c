#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct TYPE_6__ {scalar_t__ tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct pstore_record {int compressed; TYPE_2__ time; void* type; scalar_t__ ecc_notice_size; scalar_t__ id; int /*<<< orphan*/ * buf; } ;
struct TYPE_7__ {int validation_bits; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  creator_id; } ;
struct TYPE_5__ {int /*<<< orphan*/  section_type; } ;
struct cper_pstore_record {TYPE_3__ hdr; TYPE_1__ sec_hdr; int /*<<< orphan*/  data; } ;
typedef  int ssize_t ;
struct TYPE_8__ {int bufsize; } ;

/* Variables and functions */
 scalar_t__ APEI_ERST_INVALID_RECORD_ID ; 
 int /*<<< orphan*/  CPER_CREATOR_PSTORE ; 
 int /*<<< orphan*/  CPER_SECTION_TYPE_DMESG ; 
 int /*<<< orphan*/  CPER_SECTION_TYPE_DMESG_Z ; 
 int /*<<< orphan*/  CPER_SECTION_TYPE_MCE ; 
 int CPER_VALID_TIMESTAMP ; 
 int EINVAL ; 
 int EIO ; 
 int ENODEV ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* PSTORE_TYPE_DMESG ; 
 void* PSTORE_TYPE_MAX ; 
 void* PSTORE_TYPE_MCE ; 
 scalar_t__ erst_disable ; 
 int erst_get_record_id_next (int /*<<< orphan*/ *,scalar_t__*) ; 
 TYPE_4__ erst_info ; 
 int erst_read (scalar_t__,TYPE_3__*,size_t) ; 
 scalar_t__ guid_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct cper_pstore_record*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reader_pos ; 

__attribute__((used)) static ssize_t erst_reader(struct pstore_record *record)
{
	int rc;
	ssize_t len = 0;
	u64 record_id;
	struct cper_pstore_record *rcd;
	size_t rcd_len = sizeof(*rcd) + erst_info.bufsize;

	if (erst_disable)
		return -ENODEV;

	rcd = kmalloc(rcd_len, GFP_KERNEL);
	if (!rcd) {
		rc = -ENOMEM;
		goto out;
	}
skip:
	rc = erst_get_record_id_next(&reader_pos, &record_id);
	if (rc)
		goto out;

	/* no more record */
	if (record_id == APEI_ERST_INVALID_RECORD_ID) {
		rc = -EINVAL;
		goto out;
	}

	len = erst_read(record_id, &rcd->hdr, rcd_len);
	/* The record may be cleared by others, try read next record */
	if (len == -ENOENT)
		goto skip;
	else if (len < 0 || len < sizeof(*rcd)) {
		rc = -EIO;
		goto out;
	}
	if (!guid_equal(&rcd->hdr.creator_id, &CPER_CREATOR_PSTORE))
		goto skip;

	record->buf = kmalloc(len, GFP_KERNEL);
	if (record->buf == NULL) {
		rc = -ENOMEM;
		goto out;
	}
	memcpy(record->buf, rcd->data, len - sizeof(*rcd));
	record->id = record_id;
	record->compressed = false;
	record->ecc_notice_size = 0;
	if (guid_equal(&rcd->sec_hdr.section_type, &CPER_SECTION_TYPE_DMESG_Z)) {
		record->type = PSTORE_TYPE_DMESG;
		record->compressed = true;
	} else if (guid_equal(&rcd->sec_hdr.section_type, &CPER_SECTION_TYPE_DMESG))
		record->type = PSTORE_TYPE_DMESG;
	else if (guid_equal(&rcd->sec_hdr.section_type, &CPER_SECTION_TYPE_MCE))
		record->type = PSTORE_TYPE_MCE;
	else
		record->type = PSTORE_TYPE_MAX;

	if (rcd->hdr.validation_bits & CPER_VALID_TIMESTAMP)
		record->time.tv_sec = rcd->hdr.timestamp;
	else
		record->time.tv_sec = 0;
	record->time.tv_nsec = 0;

out:
	kfree(rcd);
	return (rc < 0) ? rc : (len - sizeof(*rcd));
}