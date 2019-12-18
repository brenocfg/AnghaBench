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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct scsi_mam_attribute_header {int /*<<< orphan*/ * attribute; int /*<<< orphan*/  length; } ;
struct sbuf {int dummy; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ MIN (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  sbuf_hexdump (struct sbuf*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*) ; 
 scalar_t__ scsi_2btoul (int /*<<< orphan*/ ) ; 

int
scsi_attrib_hexdump_sbuf(struct sbuf *sb, struct scsi_mam_attribute_header *hdr,
			 uint32_t valid_len, uint32_t flags,
			 uint32_t output_flags, char *error_str,
			 int error_str_len)
{
	uint32_t field_size;
	ssize_t avail_len;
	uint32_t print_len;
	uint8_t *num_ptr;
	int retval = 0;

	field_size = scsi_2btoul(hdr->length);
	avail_len = valid_len - sizeof(*hdr);
	print_len = MIN(avail_len, field_size);
	num_ptr = hdr->attribute;

	if (print_len > 0) {
		sbuf_printf(sb, "\n");
		sbuf_hexdump(sb, num_ptr, print_len, NULL, 0);
	}

	return (retval);
}