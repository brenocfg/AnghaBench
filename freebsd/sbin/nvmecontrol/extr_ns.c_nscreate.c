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
struct TYPE_5__ {int status; int cdw0; } ;
struct TYPE_4__ {int /*<<< orphan*/  cdw10; int /*<<< orphan*/  opc; } ;
struct nvme_pt_command {scalar_t__ nsze; scalar_t__ ncap; int flbas; int dps; int nmic; int len; TYPE_2__ cpl; scalar_t__ is_read; struct nvme_pt_command* buf; TYPE_1__ cmd; } ;
struct nvme_namespace_data {scalar_t__ nsze; scalar_t__ ncap; int flbas; int dps; int nmic; int len; TYPE_2__ cpl; scalar_t__ is_read; struct nvme_namespace_data* buf; TYPE_1__ cmd; } ;
struct nvme_controller_data {int oacs; scalar_t__ mic; } ;
struct cmd {int dummy; } ;
typedef  int /*<<< orphan*/  pt ;
typedef  int /*<<< orphan*/  nsdata ;
struct TYPE_6__ {scalar_t__ cap; scalar_t__ nsze; int nmic; int flbas; int lbaf; int mset; int dps; int pi; int pil; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int NONE ; 
 scalar_t__ NONE64 ; 
 int NVME_CTRLR_DATA_OACS_NSMGMT_MASK ; 
 int NVME_CTRLR_DATA_OACS_NSMGMT_SHIFT ; 
 int NVME_NS_DATA_DPS_MD_START_MASK ; 
 int NVME_NS_DATA_DPS_MD_START_SHIFT ; 
 int NVME_NS_DATA_DPS_PIT_MASK ; 
 int NVME_NS_DATA_DPS_PIT_SHIFT ; 
 int NVME_NS_DATA_FLBAS_EXTENDED_MASK ; 
 int NVME_NS_DATA_FLBAS_EXTENDED_SHIFT ; 
 int NVME_NS_DATA_FLBAS_FORMAT_MASK ; 
 int NVME_NS_DATA_FLBAS_FORMAT_SHIFT ; 
 int NVME_NS_DATA_NMIC_MAY_BE_SHARED_MASK ; 
 int NVME_NS_DATA_NMIC_MAY_BE_SHARED_SHIFT ; 
 int /*<<< orphan*/  NVME_OPC_NAMESPACE_MANAGEMENT ; 
 int /*<<< orphan*/  NVME_PASSTHROUGH_CMD ; 
 int NVME_STATUS_SC_MASK ; 
 int NVME_STATUS_SC_SHIFT ; 
 int /*<<< orphan*/  arg_help (int,char**,struct cmd const*) ; 
 scalar_t__ arg_parse (int,char**,struct cmd const*) ; 
 TYPE_3__ create_opt ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  get_res_str (int) ; 
 int /*<<< orphan*/  htole32 (int /*<<< orphan*/ ) ; 
 int ioctl (int,int /*<<< orphan*/ ,struct nvme_pt_command*) ; 
 int /*<<< orphan*/  memset (struct nvme_pt_command*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nvme_completion_is_error (TYPE_2__*) ; 
 int /*<<< orphan*/  nvme_namespace_data_swapbytes (struct nvme_pt_command*) ; 
 int /*<<< orphan*/  open_dev (int /*<<< orphan*/ ,int*,int,int) ; 
 size_t optind ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  read_controller_data (int,struct nvme_controller_data*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
nscreate(const struct cmd *f, int argc, char *argv[])
{
	struct nvme_pt_command	pt;
	struct nvme_controller_data cd;
	struct nvme_namespace_data nsdata;
	int	fd, result;

	if (arg_parse(argc, argv, f))
		return;

	if (create_opt.cap == NONE64)
		create_opt.cap = create_opt.nsze;
	if (create_opt.nsze == NONE64) {
		fprintf(stderr,
		    "Size not specified\n");
		arg_help(argc, argv, f);
	}

	open_dev(create_opt.dev, &fd, 1, 1);
	read_controller_data(fd, &cd);

	/* Check that controller can execute this command. */
	if (((cd.oacs >> NVME_CTRLR_DATA_OACS_NSMGMT_SHIFT) &
	    NVME_CTRLR_DATA_OACS_NSMGMT_MASK) == 0)
		errx(1, "controller does not support namespace management");

	/* Allow namespaces sharing if Multi-Path I/O is supported. */
	if (create_opt.nmic == NONE) {
		create_opt.nmic = cd.mic ? (NVME_NS_DATA_NMIC_MAY_BE_SHARED_MASK <<
		     NVME_NS_DATA_NMIC_MAY_BE_SHARED_SHIFT) : 0;
	}

	memset(&nsdata, 0, sizeof(nsdata));
	nsdata.nsze = create_opt.nsze;
	nsdata.ncap = create_opt.cap;
	if (create_opt.flbas == NONE)
		nsdata.flbas = ((create_opt.lbaf & NVME_NS_DATA_FLBAS_FORMAT_MASK)
		    << NVME_NS_DATA_FLBAS_FORMAT_SHIFT) |
		    ((create_opt.mset & NVME_NS_DATA_FLBAS_EXTENDED_MASK)
			<< NVME_NS_DATA_FLBAS_EXTENDED_SHIFT);
	else
		nsdata.flbas = create_opt.flbas;
	if (create_opt.dps == NONE)
		nsdata.dps = ((create_opt.pi & NVME_NS_DATA_DPS_MD_START_MASK)
		    << NVME_NS_DATA_DPS_MD_START_SHIFT) |
		    ((create_opt.pil & NVME_NS_DATA_DPS_PIT_MASK)
			<< NVME_NS_DATA_DPS_PIT_SHIFT);
	else
		nsdata.dps = create_opt.dps;
	nsdata.nmic = create_opt.nmic;
	nvme_namespace_data_swapbytes(&nsdata);

	memset(&pt, 0, sizeof(pt));
	pt.cmd.opc = NVME_OPC_NAMESPACE_MANAGEMENT;
	pt.cmd.cdw10 = htole32(0); /* create */
	pt.buf = &nsdata;
	pt.len = sizeof(struct nvme_namespace_data);
	pt.is_read = 0; /* passthrough writes data to ctrlr */
	if ((result = ioctl(fd, NVME_PASSTHROUGH_CMD, &pt)) < 0)
		errx(1, "ioctl request to %s failed: %d", argv[optind], result);

	if (nvme_completion_is_error(&pt.cpl)) {
		errx(1, "namespace creation failed: %s",
		    get_res_str((pt.cpl.status >> NVME_STATUS_SC_SHIFT) &
		    NVME_STATUS_SC_MASK));
	}
	printf("namespace %d created\n", pt.cpl.cdw0);
	exit(0);
}