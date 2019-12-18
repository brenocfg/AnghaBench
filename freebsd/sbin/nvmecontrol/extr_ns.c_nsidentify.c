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
typedef  scalar_t__ uint8_t ;
typedef  int u_int ;
struct TYPE_3__ {void* cdw10; void* nsid; int /*<<< orphan*/  opc; } ;
struct nvme_pt_command {int len; int is_read; int /*<<< orphan*/  cpl; struct nvme_namespace_data* buf; TYPE_1__ cmd; } ;
struct nvme_namespace_data {int dummy; } ;
struct nvme_controller_data {int oacs; } ;
struct cmd {int dummy; } ;
typedef  int /*<<< orphan*/  pt ;
typedef  int /*<<< orphan*/  nsdata ;
struct TYPE_4__ {scalar_t__ nsid; int /*<<< orphan*/  verbose; scalar_t__ hex; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ NONE ; 
 int NVME_CTRLR_DATA_OACS_NSMGMT_MASK ; 
 int NVME_CTRLR_DATA_OACS_NSMGMT_SHIFT ; 
 int /*<<< orphan*/  NVME_OPC_IDENTIFY ; 
 int /*<<< orphan*/  NVME_PASSTHROUGH_CMD ; 
 int /*<<< orphan*/  arg_help (int,char**,struct cmd const*) ; 
 scalar_t__ arg_parse (int,char**,struct cmd const*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 void* htole32 (int) ; 
 TYPE_2__ identify_opt ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct nvme_pt_command*) ; 
 int /*<<< orphan*/  memset (struct nvme_pt_command*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nvme_completion_is_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_namespace_data_swapbytes (struct nvme_namespace_data*) ; 
 int /*<<< orphan*/  open_dev (int /*<<< orphan*/ ,int*,int,int) ; 
 int /*<<< orphan*/  print_hex (struct nvme_namespace_data*,int) ; 
 int /*<<< orphan*/  print_namespace (struct nvme_namespace_data*) ; 
 int /*<<< orphan*/  read_controller_data (int,struct nvme_controller_data*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
nsidentify(const struct cmd *f, int argc, char *argv[])
{
	struct nvme_pt_command	pt;
	struct nvme_controller_data cd;
	struct nvme_namespace_data nsdata;
	uint8_t	*data;
	int	fd;
	u_int	i;

	if (arg_parse(argc, argv, f))
		return;
	if (identify_opt.nsid == NONE) {
		fprintf(stderr, "No valid NSID specified\n");
		arg_help(argc, argv, f);
	}
	open_dev(identify_opt.dev, &fd, 1, 1);
	read_controller_data(fd, &cd);

	/* Check that controller can execute this command. */
	if (((cd.oacs >> NVME_CTRLR_DATA_OACS_NSMGMT_SHIFT) &
	    NVME_CTRLR_DATA_OACS_NSMGMT_MASK) == 0)
		errx(1, "controller does not support namespace management");

	memset(&pt, 0, sizeof(pt));
	pt.cmd.opc = NVME_OPC_IDENTIFY;
	pt.cmd.nsid = htole32(identify_opt.nsid);
	pt.cmd.cdw10 = htole32(0x11);
	pt.buf = &nsdata;
	pt.len = sizeof(nsdata);
	pt.is_read = 1;

	if (ioctl(fd, NVME_PASSTHROUGH_CMD, &pt) < 0)
		err(1, "identify request failed");

	if (nvme_completion_is_error(&pt.cpl))
		errx(1, "identify request returned error");

	close(fd);

	data = (uint8_t *)&nsdata;
	for (i = 0; i < sizeof(nsdata); i++) {
		if (data[i] != 0)
			break;
	}
	if (i == sizeof(nsdata))
		errx(1, "namespace %d is not allocated", identify_opt.nsid);

	/* Convert data to host endian */
	nvme_namespace_data_swapbytes(&nsdata);

	if (identify_opt.hex) {
		i = sizeof(struct nvme_namespace_data);
		if (!identify_opt.verbose) {
			for (; i > 384; i--) {
				if (data[i - 1] != 0)
					break;
			}
		}
		print_hex(&nsdata, i);
		exit(0);
	}

	print_namespace(&nsdata);
	exit(0);
}