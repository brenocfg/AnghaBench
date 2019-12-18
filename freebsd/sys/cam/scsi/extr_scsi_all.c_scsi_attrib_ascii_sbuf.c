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
struct scsi_mam_attribute_header {int /*<<< orphan*/  id; int /*<<< orphan*/  attribute; int /*<<< orphan*/  length; } ;
struct sbuf {int dummy; } ;
typedef  int /*<<< orphan*/  cam_strvis_flags ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_STRVIS_FLAG_NONASCII_ESC ; 
 int /*<<< orphan*/  CAM_STRVIS_FLAG_NONASCII_RAW ; 
 int /*<<< orphan*/  CAM_STRVIS_FLAG_NONASCII_TRIM ; 
 int MIN (size_t,int) ; 
#define  SCSI_ATTR_OUTPUT_NONASCII_ESC 130 
 int SCSI_ATTR_OUTPUT_NONASCII_MASK ; 
#define  SCSI_ATTR_OUTPUT_NONASCII_RAW 129 
#define  SCSI_ATTR_OUTPUT_NONASCII_TRIM 128 
 int /*<<< orphan*/  cam_strvis_sbuf (struct sbuf*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int scsi_2btoul (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,size_t,int) ; 

int
scsi_attrib_ascii_sbuf(struct sbuf *sb, struct scsi_mam_attribute_header *hdr,
		       uint32_t valid_len, uint32_t flags,
		       uint32_t output_flags, char *error_str,
		       int error_str_len)
{
	size_t avail_len;
	uint32_t field_size, print_size;
	int retval = 0;

	avail_len = valid_len - sizeof(*hdr);
	field_size = scsi_2btoul(hdr->length);
	print_size = MIN(avail_len, field_size);

	if (print_size > 0) {
		cam_strvis_flags strvis_flags;

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
			break;
		}
		cam_strvis_sbuf(sb, hdr->attribute, print_size, strvis_flags);
	} else if (avail_len < field_size) {
		/*
		 * We only report an error if the user didn't allocate
		 * enough space to hold the full value of this field.  If
		 * the field length is 0, that is allowed by the spec.
		 * e.g. in SPC-4r37, section 7.4.2.2.5, VOLUME IDENTIFIER
		 * "This attribute indicates the current volume identifier
		 * (see SMC-3) of the medium. If the device server supports
		 * this attribute but does not have access to the volume
		 * identifier, the device server shall report this attribute
		 * with an attribute length value of zero."
		 */
		if (error_str != NULL) {
			snprintf(error_str, error_str_len, "Available "
				 "length of attribute ID 0x%.4x %zu < field "
				 "length %u", scsi_2btoul(hdr->id), avail_len,
				 field_size);
		}
		retval = 1;
	}

	return (retval);
}