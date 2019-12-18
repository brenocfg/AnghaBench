#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int EINVAL ; 
 int clearstats (int,char const**) ; 
 int dump_regs (int,char const**) ; 
 int dumpstate (int,char const**) ; 
 int filter_cmd (int,char const**,int) ; 
 int get_sge_context (int,char const**) ; 
 int load_offload_policy (int,char const**) ; 
 int loadboot (int,char const**) ; 
 int loadbootcfg (int,char const**) ; 
 int loadcfg (int,char const**) ; 
 int loadfw (int,char const**) ; 
 int memdump (int,char const**) ; 
 int modinfo (int,char const**) ; 
 int read_i2c (int,char const**) ; 
 int read_tcb (int,char const**) ; 
 int register_io (int,char const**,int) ; 
 int sched_class (int,char const**) ; 
 int sched_queue (int,char const**) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int tracer_cmd (int,char const**) ; 
 int /*<<< orphan*/  warnx (char*,char const*) ; 

__attribute__((used)) static int
run_cmd(int argc, const char *argv[])
{
	int rc = -1;
	const char *cmd = argv[0];

	/* command */
	argc--;
	argv++;

	if (!strcmp(cmd, "reg") || !strcmp(cmd, "reg32"))
		rc = register_io(argc, argv, 4);
	else if (!strcmp(cmd, "reg64"))
		rc = register_io(argc, argv, 8);
	else if (!strcmp(cmd, "regdump"))
		rc = dump_regs(argc, argv);
	else if (!strcmp(cmd, "filter"))
		rc = filter_cmd(argc, argv, 0);
	else if (!strcmp(cmd, "context"))
		rc = get_sge_context(argc, argv);
	else if (!strcmp(cmd, "loadfw"))
		rc = loadfw(argc, argv);
	else if (!strcmp(cmd, "memdump"))
		rc = memdump(argc, argv);
	else if (!strcmp(cmd, "tcb"))
		rc = read_tcb(argc, argv);
	else if (!strcmp(cmd, "i2c"))
		rc = read_i2c(argc, argv);
	else if (!strcmp(cmd, "clearstats"))
		rc = clearstats(argc, argv);
	else if (!strcmp(cmd, "tracer"))
		rc = tracer_cmd(argc, argv);
	else if (!strcmp(cmd, "modinfo"))
		rc = modinfo(argc, argv);
	else if (!strcmp(cmd, "sched-class"))
		rc = sched_class(argc, argv);
	else if (!strcmp(cmd, "sched-queue"))
		rc = sched_queue(argc, argv);
	else if (!strcmp(cmd, "loadcfg"))
		rc = loadcfg(argc, argv);
	else if (!strcmp(cmd, "loadboot"))
		rc = loadboot(argc, argv);
	else if (!strcmp(cmd, "loadboot-cfg"))
		rc = loadbootcfg(argc, argv);
	else if (!strcmp(cmd, "dumpstate"))
		rc = dumpstate(argc, argv);
	else if (!strcmp(cmd, "policy"))
		rc = load_offload_policy(argc, argv);
	else if (!strcmp(cmd, "hashfilter"))
		rc = filter_cmd(argc, argv, 1);
	else {
		rc = EINVAL;
		warnx("invalid command \"%s\"", cmd);
	}

	return (rc);
}