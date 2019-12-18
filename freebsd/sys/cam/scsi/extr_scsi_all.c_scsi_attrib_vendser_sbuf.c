#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint32_t ;
struct scsi_mam_attribute_header {scalar_t__ attribute; int /*<<< orphan*/  id; int /*<<< orphan*/  length; } ;
struct scsi_attrib_vendser {int /*<<< orphan*/  serial_num; int /*<<< orphan*/  vendor; } ;
struct sbuf {int dummy; } ;
typedef  int /*<<< orphan*/  cam_strvis_flags ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_STRVIS_FLAG_NONASCII_ESC ; 
 int /*<<< orphan*/  CAM_STRVIS_FLAG_NONASCII_RAW ; 
 int /*<<< orphan*/  CAM_STRVIS_FLAG_NONASCII_TRIM ; 
#define  SCSI_ATTR_OUTPUT_NONASCII_ESC 130 
 int SCSI_ATTR_OUTPUT_NONASCII_MASK ; 
#define  SCSI_ATTR_OUTPUT_NONASCII_RAW 129 
#define  SCSI_ATTR_OUTPUT_NONASCII_TRIM 128 
 int /*<<< orphan*/  cam_strvis_sbuf (struct sbuf*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbuf_putc (struct sbuf*,char) ; 
 int scsi_2btoul (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,...) ; 

int
scsi_attrib_vendser_sbuf(struct sbuf *sb, struct scsi_mam_attribute_header *hdr,
			 uint32_t valid_len, uint32_t flags, 
			 uint32_t output_flags, char *error_str,
			 int error_str_len)
{
	size_t avail_len;
	uint32_t field_size;
	struct scsi_attrib_vendser *vendser;
	cam_strvis_flags strvis_flags;
	int retval = 0;

	field_size = scsi_2btoul(hdr->length);
	avail_len = valid_len - sizeof(*hdr);
	if (field_size > avail_len) {
		if (error_str != NULL) {
			snprintf(error_str, error_str_len, "Available "
				 "length of attribute ID 0x%.4x %zu < field "
				 "length %u", scsi_2btoul(hdr->id), avail_len,
				 field_size);
		}
		retval = 1;
		goto bailout;
	} else if (field_size == 0) {
		/*
		 * A field size of 0 doesn't make sense here.  The device
		 * can at least give you the vendor ID, even if it can't
		 * give you the serial number.
		 */
		if (error_str != NULL) {
			snprintf(error_str, error_str_len, "The length of "
				 "attribute ID 0x%.4x is 0",
				 scsi_2btoul(hdr->id));
		}
		retval = 1;
		goto bailout;
	}
	vendser = (struct scsi_attrib_vendser *)hdr->attribute;

	switch (output_flags & SCSI_ATTR_OUTPUT_NONASCII_MASK) {
	case SCSI_ATTR_OUTPUT_NONASCII_TRIM:
		strvis_flags = CAM_STRVIS_FLAG_NONASCII_TRIM;
		break;
	case SCSI_ATTR_OUTPUT_NONASCII_RAW:
		strvis_flags = CAM_STRVIS_FLAG_NONASCII_RAW;
		break;
	case SCSI_ATTR_OUTPUT_NONASCII_ESC:
	default:
		strvis_flags = CAM_STRVIS_FLAG_NONASCII_ESC;
		break;;
	}
	cam_strvis_sbuf(sb, vendser->vendor, sizeof(vendser->vendor),
	    strvis_flags);
	sbuf_putc(sb, ' ');
	cam_strvis_sbuf(sb, vendser->serial_num, sizeof(vendser->serial_num),
	    strvis_flags);
bailout:
	return (retval);
}