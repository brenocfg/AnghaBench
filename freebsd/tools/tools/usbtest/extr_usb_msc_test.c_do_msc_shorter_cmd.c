#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  umass_bbb_cbw_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_2__ {int /*<<< orphan*/  xfer_error; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_msc_reset (int /*<<< orphan*/ ) ; 
 int libusb20_tr_bulk_intr_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 TYPE_1__ stats ; 
 int /*<<< orphan*/  xfer_out ; 

__attribute__((used)) static void
do_msc_shorter_cmd(uint8_t lun)
{
	uint8_t buffer[sizeof(umass_bbb_cbw_t)];
	int actlen;
	int error;
	int x;

	memset(buffer, 0, sizeof(buffer));

	for (x = 0; x != (sizeof(buffer) - 1); x++) {
		error = libusb20_tr_bulk_intr_sync(xfer_out,
		    buffer, x, &actlen, 250);

		printf("Sent short %d of %d bytes wrapper block, "
		    "status = %d\n", x, (int)(sizeof(buffer) - 1),
		    error);

		do_msc_reset(lun);

		if (error != 0) {
			printf("ERROR: Too short command wrapper "
			    "was not accepted\n");
			stats.xfer_error++;
			break;
		}
	}
}