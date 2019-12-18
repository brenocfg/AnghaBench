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
struct nvme_sanitize_status_page {int sstat; int sprog; } ;
struct TYPE_3__ {void* cdw11; void* cdw10; int /*<<< orphan*/  opc; } ;
struct nvme_pt_command {int /*<<< orphan*/  cpl; TYPE_1__ cmd; } ;
struct nvme_controller_data {int sanicap; int nn; } ;
struct cmd {int dummy; } ;
typedef  int /*<<< orphan*/  ss ;
typedef  int /*<<< orphan*/  pt ;
struct TYPE_4__ {int owpass; char* dev; int ndas; int oipbp; int ause; int ovrpat; scalar_t__ reportonly; int /*<<< orphan*/ * sanact; } ;

/* Variables and functions */
 int NVME_CTRLR_DATA_SANICAP_BES_MASK ; 
 int NVME_CTRLR_DATA_SANICAP_BES_SHIFT ; 
 int NVME_CTRLR_DATA_SANICAP_CES_MASK ; 
 int NVME_CTRLR_DATA_SANICAP_CES_SHIFT ; 
 int NVME_CTRLR_DATA_SANICAP_OWS_MASK ; 
 int NVME_CTRLR_DATA_SANICAP_OWS_SHIFT ; 
 int /*<<< orphan*/  NVME_GLOBAL_NAMESPACE_TAG ; 
 int /*<<< orphan*/  NVME_LOG_SANITIZE_STATUS ; 
 int /*<<< orphan*/  NVME_OPC_SANITIZE ; 
 int /*<<< orphan*/  NVME_PASSTHROUGH_CMD ; 
#define  NVME_SS_PAGE_SSTAT_STATUS_COMPLETED 132 
#define  NVME_SS_PAGE_SSTAT_STATUS_COMPLETEDWD 131 
#define  NVME_SS_PAGE_SSTAT_STATUS_FAILED 130 
#define  NVME_SS_PAGE_SSTAT_STATUS_INPROG 129 
 int NVME_SS_PAGE_SSTAT_STATUS_MASK ; 
#define  NVME_SS_PAGE_SSTAT_STATUS_NEVER 128 
 int NVME_SS_PAGE_SSTAT_STATUS_SHIFT ; 
 int /*<<< orphan*/  arg_help (int,char**,struct cmd const*) ; 
 scalar_t__ arg_parse (int,char**,struct cmd const*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  get_nsid (int,char**,scalar_t__*) ; 
 void* htole32 (int) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct nvme_pt_command*) ; 
 int /*<<< orphan*/  memset (struct nvme_pt_command*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nvme_completion_is_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  open_dev (char*,int*,int,int) ; 
 TYPE_2__ opt ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  read_controller_data (int,struct nvme_controller_data*) ; 
 int /*<<< orphan*/  read_logpage (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nvme_sanitize_status_page*,int) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
sanitize(const struct cmd *f, int argc, char *argv[])
{
	struct nvme_controller_data	cd;
	struct nvme_pt_command		pt;
	struct nvme_sanitize_status_page ss;
	char				*path;
	uint32_t			nsid;
	int				sanact = 0, fd, delay = 1;

	if (arg_parse(argc, argv, f))
		return;

	if (opt.sanact == NULL) {
		if (!opt.reportonly) {
			fprintf(stderr, "Sanitize Action is not specified\n");
			arg_help(argc, argv, f);
		}
	} else {
		if (strcmp(opt.sanact, "exitfailure") == 0)
			sanact = 1;
		else if (strcmp(opt.sanact, "block") == 0)
			sanact = 2;
		else if (strcmp(opt.sanact, "overwrite") == 0)
			sanact = 3;
		else if (strcmp(opt.sanact, "crypto") == 0)
			sanact = 4;
		else {
			fprintf(stderr, "Incorrect Sanitize Action value\n");
			arg_help(argc, argv, f);
		}
	}
	if (opt.owpass == 0 || opt.owpass > 16) {
		fprintf(stderr, "Incorrect Overwrite Pass Count value\n");
		arg_help(argc, argv, f);
	}

	open_dev(opt.dev, &fd, 1, 1);
	get_nsid(fd, &path, &nsid);
	if (nsid != 0) {
		close(fd);
		open_dev(path, &fd, 1, 1);
	}
	free(path);

	if (opt.reportonly)
		goto wait;

	/* Check that controller can execute this command. */
	read_controller_data(fd, &cd);
	if (((cd.sanicap >> NVME_CTRLR_DATA_SANICAP_BES_SHIFT) &
	     NVME_CTRLR_DATA_SANICAP_BES_MASK) == 0 && sanact == 2)
		errx(1, "controller does not support Block Erase");
	if (((cd.sanicap >> NVME_CTRLR_DATA_SANICAP_OWS_SHIFT) &
	     NVME_CTRLR_DATA_SANICAP_OWS_MASK) == 0 && sanact == 3)
		errx(1, "controller does not support Overwrite");
	if (((cd.sanicap >> NVME_CTRLR_DATA_SANICAP_CES_SHIFT) &
	     NVME_CTRLR_DATA_SANICAP_CES_MASK) == 0 && sanact == 4)
		errx(1, "controller does not support Crypto Erase");

	/*
	 * If controller supports only one namespace, we may sanitize it.
	 * If there can be more, make user explicit in his commands.
	 */
	if (nsid != 0 && cd.nn > 1)
		errx(1, "can't sanitize one of namespaces, specify controller");

	memset(&pt, 0, sizeof(pt));
	pt.cmd.opc = NVME_OPC_SANITIZE;
	pt.cmd.cdw10 = htole32((opt.ndas << 9) | (opt.oipbp << 8) |
	    ((opt.owpass & 0xf) << 4) | (opt.ause << 3) | sanact);
	pt.cmd.cdw11 = htole32(opt.ovrpat);

	if (ioctl(fd, NVME_PASSTHROUGH_CMD, &pt) < 0)
		err(1, "sanitize request failed");

	if (nvme_completion_is_error(&pt.cpl))
		errx(1, "sanitize request returned error");

wait:
	read_logpage(fd, NVME_LOG_SANITIZE_STATUS,
	    NVME_GLOBAL_NAMESPACE_TAG, 0, 0, 0, &ss, sizeof(ss));
	switch ((ss.sstat >> NVME_SS_PAGE_SSTAT_STATUS_SHIFT) &
	    NVME_SS_PAGE_SSTAT_STATUS_MASK) {
	case NVME_SS_PAGE_SSTAT_STATUS_NEVER:
		printf("Never sanitized");
		break;
	case NVME_SS_PAGE_SSTAT_STATUS_COMPLETED:
		printf("Sanitize completed");
		break;
	case NVME_SS_PAGE_SSTAT_STATUS_INPROG:
		printf("Sanitize in progress: %u%% (%u/65535)\r",
		    (ss.sprog * 100 + 32768) / 65536, ss.sprog);
		fflush(stdout);
		if (delay < 16)
			delay++;
		sleep(delay);
		goto wait;
	case NVME_SS_PAGE_SSTAT_STATUS_FAILED:
		printf("Sanitize failed");
		break;
	case NVME_SS_PAGE_SSTAT_STATUS_COMPLETEDWD:
		printf("Sanitize completed with deallocation");
		break;
	default:
		printf("Sanitize status unknown");
		break;
	}
	if (delay > 1)
		printf("                       ");
	printf("\n");

	close(fd);
	exit(0);
}