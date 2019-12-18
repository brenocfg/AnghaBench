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
typedef  int /*<<< orphan*/  vendor ;
typedef  char* uintmax_t ;
typedef  char* uint8_t ;
struct smp_report_manuf_info_response {int sas_11_format; char* comp_revision; int /*<<< orphan*/  vendor_specific; int /*<<< orphan*/  comp_id; int /*<<< orphan*/  comp_vendor; int /*<<< orphan*/  crc; int /*<<< orphan*/  revision; int /*<<< orphan*/  product; int /*<<< orphan*/  vendor; int /*<<< orphan*/  expander_change_count; } ;
struct sbuf {int dummy; } ;
typedef  int /*<<< orphan*/  revision ;
typedef  int /*<<< orphan*/  product ;
typedef  int /*<<< orphan*/  comp_vendor ;

/* Variables and functions */
 int SMP_RMI_SAS11_FORMAT ; 
 int /*<<< orphan*/  cam_strvis (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,...) ; 
 char* scsi_2btoul (int /*<<< orphan*/ ) ; 
 scalar_t__ scsi_8btou64 (int /*<<< orphan*/ ) ; 
 char* smp_yesno (int) ; 

void
smp_report_manuf_info_sbuf(struct smp_report_manuf_info_response *response,
			   int response_len, struct sbuf *sb)
{
	char vendor[16], product[48], revision[16];
	char comp_vendor[16];

	sbuf_printf(sb, "Report Manufacturer Information\n");
	sbuf_printf(sb, "Expander Change count: %d\n",
		    scsi_2btoul(response->expander_change_count));
	sbuf_printf(sb, "SAS 1.1 Format: %s\n",
		    smp_yesno(response->sas_11_format & SMP_RMI_SAS11_FORMAT));
	cam_strvis(vendor, response->vendor, sizeof(response->vendor),
		   sizeof(vendor));
	cam_strvis(product, response->product, sizeof(response->product),
		   sizeof(product));
	cam_strvis(revision, response->revision, sizeof(response->revision),
		   sizeof(revision));
	sbuf_printf(sb, "<%s %s %s>\n", vendor, product, revision);

	if ((response->sas_11_format & SMP_RMI_SAS11_FORMAT) == 0) {
		uint8_t *curbyte;
		int line_start, line_cursor;

		sbuf_printf(sb, "Vendor Specific Data:\n");

		/*
		 * Print out the bytes roughly in the style of hd(1), but
		 * without the extra ASCII decoding.  Hexadecimal line
		 * numbers on the left, and 16 bytes per line, with an
		 * extra space after the first 8 bytes.
		 *
		 * It would be nice if this sort of thing were available
		 * in a library routine.
		 */
		for (curbyte = (uint8_t *)&response->comp_vendor, line_start= 1,
		     line_cursor = 0; curbyte < (uint8_t *)&response->crc;
		     curbyte++, line_cursor++) {
			if (line_start != 0) {
				sbuf_printf(sb, "%08lx  ",
					    (unsigned long)(curbyte -
					    (uint8_t *)response));
				line_start = 0;
				line_cursor = 0;
			}
			sbuf_printf(sb, "%02x", *curbyte);

			if (line_cursor == 15) {
				sbuf_printf(sb, "\n");
				line_start = 1;
			} else
				sbuf_printf(sb, " %s", (line_cursor == 7) ?
					    " " : "");
		}
		if (line_cursor != 16)
			sbuf_printf(sb, "\n");
		return;
	}

	cam_strvis(comp_vendor, response->comp_vendor,
		   sizeof(response->comp_vendor), sizeof(comp_vendor));
	sbuf_printf(sb, "Component Vendor: %s\n", comp_vendor);
	sbuf_printf(sb, "Component ID: %#x\n", scsi_2btoul(response->comp_id));
	sbuf_printf(sb, "Component Revision: %#x\n", response->comp_revision);
	sbuf_printf(sb, "Vendor Specific: 0x%016jx\n",
		    (uintmax_t)scsi_8btou64(response->vendor_specific));
}