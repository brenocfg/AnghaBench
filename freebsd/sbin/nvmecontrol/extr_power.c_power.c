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
struct nvme_controller_data {int dummy; } ;
struct cmd {int dummy; } ;
struct TYPE_2__ {scalar_t__ power; int /*<<< orphan*/  workload; scalar_t__ list; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ POWER_NONE ; 
 int /*<<< orphan*/  arg_help (int,char**,struct cmd const*) ; 
 int /*<<< orphan*/  arg_parse (int,char**,struct cmd const*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  open_dev (int /*<<< orphan*/ ,int*,int,int) ; 
 TYPE_1__ opt ; 
 int /*<<< orphan*/  power_list (struct nvme_controller_data*) ; 
 int /*<<< orphan*/  power_set (int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  power_show (int) ; 
 int /*<<< orphan*/  read_controller_data (int,struct nvme_controller_data*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
power(const struct cmd *f, int argc, char *argv[])
{
	struct nvme_controller_data	cdata;
	int				fd;

	arg_parse(argc, argv, f);

	if (opt.list && opt.power != POWER_NONE) {
		fprintf(stderr, "Can't set power and list power states\n");
		arg_help(argc, argv, f);
	}

	open_dev(opt.dev, &fd, 1, 1);

	if (opt.list) {
		read_controller_data(fd, &cdata);
		power_list(&cdata);
		goto out;
	}

	if (opt.power != POWER_NONE) {
		power_set(fd, opt.power, opt.workload, 0);
		goto out;
	}
	power_show(fd);

out:
	close(fd);
	exit(0);
}