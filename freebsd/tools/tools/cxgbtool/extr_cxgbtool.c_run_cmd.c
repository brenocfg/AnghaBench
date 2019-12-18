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
 int clear_stats (int,char**,int,char const*) ; 
 int conf_pm (int,char**,int,char const*) ; 
 int dump_mc7 (int,char**,int,char const*) ; 
 int dump_regs (int,char**,int,char const*) ; 
 int dump_tcam (int,char**,int,char const*) ; 
 int filter_config (int,char**,int,char const*) ; 
 int get_sge_context (int,char**,int,char const*) ; 
 int get_sge_desc (int,char**,int,char const*) ; 
 int get_tcb2 (int,char**,int,char const*) ; 
 int get_up_ioqs (int,char**,int,char const*) ; 
 int get_up_la (int,char**,int,char const*) ; 
 int load_boot (int,char**,int,char const*) ; 
 int load_fw (int,char**,int,char const*) ; 
 int mdio_io (int,char**,int,char const*) ; 
 int meminfo (int,char**,int,char const*) ; 
 int mtu_tab_op (int,char**,int,char const*) ; 
 int pktsched (int,char**,int,char const*) ; 
 int proto_sram_op (int,char**,int,char const*) ; 
 int qset_config (int,char**,int,char const*) ; 
 int qset_num_config (int,char**,int,char const*) ; 
 int register_io (int,char**,int,char const*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int trace_config (int,char**,int,char const*) ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
run_cmd(int argc, char *argv[], const char *iff_name)
{
	int r = -1;

	if (!strcmp(argv[2], "reg"))
		r = register_io(argc, argv, 3, iff_name);
	else if (!strcmp(argv[2], "mdio"))
		r = mdio_io(argc, argv, 3, iff_name);
	else if (!strcmp(argv[2], "mtus"))
		r = mtu_tab_op(argc, argv, 3, iff_name);
	else if (!strcmp(argv[2], "pm"))
		r = conf_pm(argc, argv, 3, iff_name);
	else if (!strcmp(argv[2], "regdump"))
		r = dump_regs(argc, argv, 3, iff_name);
	else if (!strcmp(argv[2], "tcamdump"))
		r = dump_tcam(argc, argv, 3, iff_name);
	else if (!strcmp(argv[2], "memdump"))
		r = dump_mc7(argc, argv, 3, iff_name);
	else if (!strcmp(argv[2], "meminfo"))
		r = meminfo(argc, argv, 3, iff_name);
	else if (!strcmp(argv[2], "context"))
		r = get_sge_context(argc, argv, 3, iff_name);
	else if (!strcmp(argv[2], "desc"))
		r = get_sge_desc(argc, argv, 3, iff_name);
	else if (!strcmp(argv[2], "loadfw"))
		r = load_fw(argc, argv, 3, iff_name);
	else if (!strcmp(argv[2], "loadboot"))
		r = load_boot(argc, argv, 3, iff_name);
	else if (!strcmp(argv[2], "proto"))
		r = proto_sram_op(argc, argv, 3, iff_name);
	else if (!strcmp(argv[2], "qset"))
		r = qset_config(argc, argv, 3, iff_name);
	else if (!strcmp(argv[2], "qsets"))
		r = qset_num_config(argc, argv, 3, iff_name);
	else if (!strcmp(argv[2], "trace"))
		r = trace_config(argc, argv, 3, iff_name);
	else if (!strcmp(argv[2], "pktsched"))
		r = pktsched(argc, argv, 3, iff_name);
	else if (!strcmp(argv[2], "tcb"))
		r = get_tcb2(argc, argv, 3, iff_name);
	else if (!strcmp(argv[2], "filter"))
		r = filter_config(argc, argv, 3, iff_name);
	else if (!strcmp(argv[2], "clearstats"))
		r = clear_stats(argc, argv, 3, iff_name);
	else if (!strcmp(argv[2], "la"))
		r = get_up_la(argc, argv, 3, iff_name);
	else if (!strcmp(argv[2], "ioqs"))
		r = get_up_ioqs(argc, argv, 3, iff_name);

	if (r == -1)
		usage(stderr);

	return (0);
}