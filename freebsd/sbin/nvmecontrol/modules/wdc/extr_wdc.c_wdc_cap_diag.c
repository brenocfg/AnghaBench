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
typedef  int /*<<< orphan*/  tmpl ;
struct cmd {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/ * template; } ;

/* Variables and functions */
 int MAXPATHLEN ; 
 int /*<<< orphan*/  WDC_NVME_CAP_DIAG_CMD ; 
 int /*<<< orphan*/  WDC_NVME_CAP_DIAG_OPCODE ; 
 int /*<<< orphan*/  arg_help (int,char**,struct cmd const*) ; 
 scalar_t__ arg_parse (int,char**,struct cmd const*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  open_dev (int /*<<< orphan*/ ,int*,int,int) ; 
 TYPE_1__ opt ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wdc_do_dump (int,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
wdc_cap_diag(const struct cmd *f, int argc, char *argv[])
{
	char tmpl[MAXPATHLEN];
 	int fd;

	if (arg_parse(argc, argv, f))
		return;
	if (opt.template == NULL) {
		fprintf(stderr, "Missing template arg.\n");
		arg_help(argc, argv, f);
	}
	strlcpy(tmpl, opt.template, sizeof(tmpl));
	open_dev(opt.dev, &fd, 1, 1);
	wdc_do_dump(fd, tmpl, "cap_diag", WDC_NVME_CAP_DIAG_OPCODE,
	    WDC_NVME_CAP_DIAG_CMD, 4);

	close(fd);

	exit(1);	
}