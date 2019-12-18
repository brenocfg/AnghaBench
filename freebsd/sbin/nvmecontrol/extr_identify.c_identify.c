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
typedef  scalar_t__ uint32_t ;
struct cmd {int dummy; } ;
struct TYPE_2__ {char* dev; scalar_t__ nsid; } ;

/* Variables and functions */
 scalar_t__ NONE ; 
 int /*<<< orphan*/  arg_parse (int,char**,struct cmd const*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  get_nsid (int,char**,scalar_t__*) ; 
 int /*<<< orphan*/  identify_ctrlr (int) ; 
 int /*<<< orphan*/  identify_ns (int,scalar_t__) ; 
 int /*<<< orphan*/  open_dev (char*,int*,int,int) ; 
 TYPE_1__ opt ; 

__attribute__((used)) static void
identify(const struct cmd *f, int argc, char *argv[])
{
	char		*path;
	int		fd;
	uint32_t	nsid;

	arg_parse(argc, argv, f);

	open_dev(opt.dev, &fd, 1, 1);
	get_nsid(fd, &path, &nsid);
	if (nsid != 0) {
		/*
		 * We got namespace device, but we need to send IDENTIFY
		 * commands to the controller, not the namespace, since it
		 * is an admin cmd.  The namespace ID will be specified in
		 * the IDENTIFY command itself.
		 */
		close(fd);
		open_dev(path, &fd, 1, 1);
	}
	free(path);
	if (opt.nsid != NONE)
		nsid = opt.nsid;

	if (nsid == 0)
		identify_ctrlr(fd);
	else
		identify_ns(fd, nsid);
}