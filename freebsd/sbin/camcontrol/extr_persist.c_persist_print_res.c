#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uintmax_t ;
typedef  int uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  extent_length; int /*<<< orphan*/  scopetype; int /*<<< orphan*/  scope_addr; int /*<<< orphan*/  reservation; } ;
struct TYPE_3__ {int /*<<< orphan*/  generation; } ;
struct scsi_per_res_in_rsrv {TYPE_2__ data; TYPE_1__ header; } ;
struct scsi_per_res_in_header {int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int MIN (int,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  persist_print_scopetype (int /*<<< orphan*/ ) ; 
 int scsi_2btoul (int /*<<< orphan*/ ) ; 
 int scsi_4btoul (int /*<<< orphan*/ ) ; 
 scalar_t__ scsi_8btou64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  warnx (char*,int) ; 

__attribute__((used)) static void
persist_print_res(struct scsi_per_res_in_header *hdr, uint32_t valid_len)
{
	uint32_t length;
	struct scsi_per_res_in_rsrv *res;

	length = scsi_4btoul(hdr->length);
	length = MIN(length, valid_len);

	res = (struct scsi_per_res_in_rsrv *)hdr;

	if (length < sizeof(res->data) - sizeof(res->data.extent_length)) {
		if (length == 0)
			fprintf(stdout, "No reservations.\n");
		else
			warnx("unable to print reservation, only got %u "
			      "valid bytes", length);
		return;
	}
	fprintf(stdout, "PRgeneration: %#x\n",
		scsi_4btoul(res->header.generation));
	fprintf(stdout, "Reservation Key: %#jx\n",
		(uintmax_t)scsi_8btou64(res->data.reservation));
	fprintf(stdout, "Scope address: %#x\n",
		scsi_4btoul(res->data.scope_addr));

	persist_print_scopetype(res->data.scopetype);

	fprintf(stdout, "Extent length: %u\n",
		scsi_2btoul(res->data.extent_length));
}