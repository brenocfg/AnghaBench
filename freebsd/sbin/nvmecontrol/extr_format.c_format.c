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
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {void* cdw10; void* nsid; int /*<<< orphan*/  opc; } ;
struct nvme_pt_command {int /*<<< orphan*/  cpl; TYPE_1__ cmd; } ;
struct nvme_namespace_data {int flbas; int nlbaf; int dps; } ;
struct nvme_controller_data {int oacs; int fna; } ;
struct cmd {int dummy; } ;
typedef  int /*<<< orphan*/  pt ;
struct TYPE_4__ {int Cflag; int ses; char* dev; int lbaf; int ms; int pi; int pil; scalar_t__ Eflag; } ;

/* Variables and functions */
 int NVME_CTRLR_DATA_FNA_CRYPTO_ERASE_MASK ; 
 int NVME_CTRLR_DATA_FNA_CRYPTO_ERASE_SHIFT ; 
 int NVME_CTRLR_DATA_FNA_ERASE_ALL_MASK ; 
 int NVME_CTRLR_DATA_FNA_ERASE_ALL_SHIFT ; 
 int NVME_CTRLR_DATA_FNA_FORMAT_ALL_MASK ; 
 int NVME_CTRLR_DATA_FNA_FORMAT_ALL_SHIFT ; 
 int NVME_CTRLR_DATA_OACS_FORMAT_MASK ; 
 int NVME_CTRLR_DATA_OACS_FORMAT_SHIFT ; 
 scalar_t__ NVME_GLOBAL_NAMESPACE_TAG ; 
 int NVME_NS_DATA_DPS_MD_START_MASK ; 
 int NVME_NS_DATA_DPS_MD_START_SHIFT ; 
 int NVME_NS_DATA_DPS_PIT_MASK ; 
 int NVME_NS_DATA_DPS_PIT_SHIFT ; 
 int NVME_NS_DATA_FLBAS_EXTENDED_MASK ; 
 int NVME_NS_DATA_FLBAS_EXTENDED_SHIFT ; 
 int NVME_NS_DATA_FLBAS_FORMAT_MASK ; 
 int NVME_NS_DATA_FLBAS_FORMAT_SHIFT ; 
 int /*<<< orphan*/  NVME_OPC_FORMAT_NVM ; 
 int /*<<< orphan*/  NVME_PASSTHROUGH_CMD ; 
 int SES_CRYPTO ; 
 int SES_NONE ; 
 int SES_USER ; 
 int /*<<< orphan*/  arg_help (int,char**,struct cmd const*) ; 
 scalar_t__ arg_parse (int,char**,struct cmd const*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  get_nsid (int,char**,scalar_t__*) ; 
 void* htole32 (int) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct nvme_pt_command*) ; 
 int /*<<< orphan*/  memset (struct nvme_pt_command*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nvme_completion_is_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  open_dev (char const*,int*,int,int) ; 
 TYPE_2__ opt ; 
 int /*<<< orphan*/  read_controller_data (int,struct nvme_controller_data*) ; 
 int /*<<< orphan*/  read_namespace_data (int,scalar_t__,struct nvme_namespace_data*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
format(const struct cmd *f, int argc, char *argv[])
{
	struct nvme_controller_data	cd;
	struct nvme_namespace_data	nsd;
	struct nvme_pt_command		pt;
	char				*path;
	const char			*target;
	uint32_t			nsid;
	int				lbaf, ms, pi, pil, ses, fd;

	if (arg_parse(argc, argv, f))
		return;

	if ((int)opt.Eflag + opt.Cflag + (opt.ses != SES_NONE) > 1) {
		fprintf(stderr,
		    "Only one of -E, -C or -s may be specified\n");
		arg_help(argc, argv, f);
	}

	target = opt.dev;
	lbaf = opt.lbaf;
	ms = opt.ms;
	pi = opt.pi;
	pil = opt.pil;
	if (opt.Eflag)
		ses = SES_USER;
	else if (opt.Cflag)
		ses = SES_CRYPTO;
	else
		ses = opt.ses;

	open_dev(target, &fd, 1, 1);
	get_nsid(fd, &path, &nsid);
	if (nsid == 0) {
		nsid = NVME_GLOBAL_NAMESPACE_TAG;
	} else {
		/*
		 * We send FORMAT commands to the controller, not the namespace,
		 * since it is an admin cmd.  The namespace ID will be specified
		 * in the command itself.  So parse the namespace's device node
		 * string to get the controller substring and namespace ID.
		 */
		close(fd);
		open_dev(path, &fd, 1, 1);
	}
	free(path);

	/* Check that controller can execute this command. */
	read_controller_data(fd, &cd);
	if (((cd.oacs >> NVME_CTRLR_DATA_OACS_FORMAT_SHIFT) &
	    NVME_CTRLR_DATA_OACS_FORMAT_MASK) == 0)
		errx(1, "controller does not support format");
	if (((cd.fna >> NVME_CTRLR_DATA_FNA_CRYPTO_ERASE_SHIFT) &
	    NVME_CTRLR_DATA_FNA_CRYPTO_ERASE_MASK) == 0 && ses == SES_CRYPTO)
		errx(1, "controller does not support cryptographic erase");

	if (nsid != NVME_GLOBAL_NAMESPACE_TAG) {
		if (((cd.fna >> NVME_CTRLR_DATA_FNA_FORMAT_ALL_SHIFT) &
		    NVME_CTRLR_DATA_FNA_FORMAT_ALL_MASK) && ses == SES_NONE)
			errx(1, "controller does not support per-NS format");
		if (((cd.fna >> NVME_CTRLR_DATA_FNA_ERASE_ALL_SHIFT) &
		    NVME_CTRLR_DATA_FNA_ERASE_ALL_MASK) && ses != SES_NONE)
			errx(1, "controller does not support per-NS erase");

		/* Try to keep previous namespace parameters. */
		read_namespace_data(fd, nsid, &nsd);
		if (lbaf < 0)
			lbaf = (nsd.flbas >> NVME_NS_DATA_FLBAS_FORMAT_SHIFT)
			    & NVME_NS_DATA_FLBAS_FORMAT_MASK;
		if (lbaf > nsd.nlbaf)
			errx(1, "LBA format is out of range");
		if (ms < 0)
			ms = (nsd.flbas >> NVME_NS_DATA_FLBAS_EXTENDED_SHIFT)
			    & NVME_NS_DATA_FLBAS_EXTENDED_MASK;
		if (pi < 0)
			pi = (nsd.dps >> NVME_NS_DATA_DPS_MD_START_SHIFT)
			    & NVME_NS_DATA_DPS_MD_START_MASK;
		if (pil < 0)
			pil = (nsd.dps >> NVME_NS_DATA_DPS_PIT_SHIFT)
			    & NVME_NS_DATA_DPS_PIT_MASK;
	} else {

		/* We have no previous parameters, so default to zeroes. */
		if (lbaf < 0)
			lbaf = 0;
		if (ms < 0)
			ms = 0;
		if (pi < 0)
			pi = 0;
		if (pil < 0)
			pil = 0;
	}

	memset(&pt, 0, sizeof(pt));
	pt.cmd.opc = NVME_OPC_FORMAT_NVM;
	pt.cmd.nsid = htole32(nsid);
	pt.cmd.cdw10 = htole32((ses << 9) + (pil << 8) + (pi << 5) +
	    (ms << 4) + lbaf);

	if (ioctl(fd, NVME_PASSTHROUGH_CMD, &pt) < 0)
		err(1, "format request failed");

	if (nvme_completion_is_error(&pt.cpl))
		errx(1, "format request returned error");
	close(fd);
	exit(0);
}