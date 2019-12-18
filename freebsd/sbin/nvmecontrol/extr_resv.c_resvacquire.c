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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  cdw10; int /*<<< orphan*/  opc; } ;
struct nvme_pt_command {int len; int /*<<< orphan*/  cpl; scalar_t__ is_read; int /*<<< orphan*/ ** buf; TYPE_1__ cmd; } ;
struct cmd {int dummy; } ;
typedef  int /*<<< orphan*/  pt ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_4__ {int racqa; int rtype; int /*<<< orphan*/  prkey; int /*<<< orphan*/  crkey; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_OPC_RESERVATION_ACQUIRE ; 
 int /*<<< orphan*/  NVME_PASSTHROUGH_CMD ; 
 TYPE_2__ acquire_opt ; 
 int /*<<< orphan*/  arg_help (int,char**,struct cmd const*) ; 
 scalar_t__ arg_parse (int,char**,struct cmd const*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  get_nsid (int,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  htole32 (int) ; 
 int /*<<< orphan*/  htole64 (int /*<<< orphan*/ ) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct nvme_pt_command*) ; 
 int /*<<< orphan*/  memset (struct nvme_pt_command*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nvme_completion_is_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  open_dev (int /*<<< orphan*/ ,int*,int,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
resvacquire(const struct cmd *f, int argc, char *argv[])
{
	struct nvme_pt_command	pt;
	uint64_t	data[2];
	int		fd;
	uint32_t	nsid;

	if (arg_parse(argc, argv, f))
		return;
	open_dev(acquire_opt.dev, &fd, 1, 1);
	get_nsid(fd, NULL, &nsid);
	if (nsid == 0) {
		fprintf(stderr, "This command require namespace-id\n");
		arg_help(argc, argv, f);
	}

	data[0] = htole64(acquire_opt.crkey);
	data[1] = htole64(acquire_opt.prkey);

	memset(&pt, 0, sizeof(pt));
	pt.cmd.opc = NVME_OPC_RESERVATION_ACQUIRE;
	pt.cmd.cdw10 = htole32((acquire_opt.racqa & 7) |
	    (acquire_opt.rtype << 8));
	pt.buf = &data;
	pt.len = sizeof(data);
	pt.is_read = 0;

	if (ioctl(fd, NVME_PASSTHROUGH_CMD, &pt) < 0)
		err(1, "acquire request failed");

	if (nvme_completion_is_error(&pt.cpl))
		errx(1, "acquire request returned error");

	close(fd);
	exit(0);
}