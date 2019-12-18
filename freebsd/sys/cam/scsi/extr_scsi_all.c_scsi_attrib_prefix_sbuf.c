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
struct scsi_mam_attribute_header {int byte2; int /*<<< orphan*/  length; int /*<<< orphan*/  id; } ;
struct sbuf {int dummy; } ;

/* Variables and functions */
 int SCSI_ATTR_OUTPUT_FIELD_DESC ; 
 int SCSI_ATTR_OUTPUT_FIELD_MASK ; 
 int SCSI_ATTR_OUTPUT_FIELD_NONE ; 
 int SCSI_ATTR_OUTPUT_FIELD_NUM ; 
 int SCSI_ATTR_OUTPUT_FIELD_RW ; 
 int SCSI_ATTR_OUTPUT_FIELD_SIZE ; 
 int SMA_READ_ONLY ; 
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,...) ; 
 int scsi_2btoul (int /*<<< orphan*/ ) ; 

void
scsi_attrib_prefix_sbuf(struct sbuf *sb, uint32_t output_flags,
			struct scsi_mam_attribute_header *hdr,
			uint32_t valid_len, const char *desc)
{
	int need_space = 0;
	uint32_t len;
	uint32_t id;

	/*
	 * We can't do anything if we don't have enough valid data for the
	 * header.
	 */
	if (valid_len < sizeof(*hdr))
		return;

	id = scsi_2btoul(hdr->id);
	/*
	 * Note that we print out the value of the attribute listed in the
	 * header, regardless of whether we actually got that many bytes
	 * back from the device through the controller.  A truncated result
	 * could be the result of a failure to ask for enough data; the
	 * header indicates how many bytes are allocated for this attribute
	 * in the MAM.
	 */
	len = scsi_2btoul(hdr->length);

	if ((output_flags & SCSI_ATTR_OUTPUT_FIELD_MASK) ==
	    SCSI_ATTR_OUTPUT_FIELD_NONE)
		return;

	if ((output_flags & SCSI_ATTR_OUTPUT_FIELD_DESC)
	 && (desc != NULL)) {
		sbuf_printf(sb, "%s", desc);
		need_space = 1;
	}

	if (output_flags & SCSI_ATTR_OUTPUT_FIELD_NUM) {
		sbuf_printf(sb, "%s(0x%.4x)", (need_space) ? " " : "", id);
		need_space = 0;
	}

	if (output_flags & SCSI_ATTR_OUTPUT_FIELD_SIZE) {
		sbuf_printf(sb, "%s[%d]", (need_space) ? " " : "", len);
		need_space = 0;
	}
	if (output_flags & SCSI_ATTR_OUTPUT_FIELD_RW) {
		sbuf_printf(sb, "%s(%s)", (need_space) ? " " : "",
			    (hdr->byte2 & SMA_READ_ONLY) ? "RO" : "RW");
	}
	sbuf_printf(sb, ": ");
}