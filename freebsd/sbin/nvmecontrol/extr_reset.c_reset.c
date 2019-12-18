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
struct cmd {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_RESET_CONTROLLER ; 
 int /*<<< orphan*/  arg_parse (int,char**,struct cmd const*) ; 
 int /*<<< orphan*/  err (int,char*,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  open_dev (int /*<<< orphan*/ ,int*,int,int) ; 
 TYPE_1__ opt ; 
 size_t optind ; 

__attribute__((used)) static void
reset(const struct cmd *f, int argc, char *argv[])
{
	int	fd;

	arg_parse(argc, argv, f);
	open_dev(opt.dev, &fd, 1, 1);

	if (ioctl(fd, NVME_RESET_CONTROLLER) < 0)
		err(1, "reset request to %s failed", argv[optind]);

	exit(0);
}