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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 char* progname ; 
 int /*<<< orphan*/ * stderr ; 

__attribute__((used)) static void
usage(FILE *fp)
{
	fprintf(fp, "Usage: %s <interface> [operation]\n", progname);
	fprintf(fp,
	    	"\tclearstats                          clear MAC statistics\n"
		"\tcontext <type> <id>                 show an SGE context\n"
		"\tdesc <qset> <queue> <idx> [<cnt>]   dump SGE descriptors\n"
		"\tfilter <idx> [<param> <val>] ...    set a filter\n"
		"\tfilter <idx> delete|clear           delete a filter\n"
		"\tfilter list                         list all filters\n"
		"\tioqs                                dump uP IOQs\n"
		"\tla                                  dump uP logic analyzer info\n"
		"\tloadboot <boot image>               download boot image\n"
		"\tloadfw <FW image>                   download firmware\n"
		"\tmdio <phy_addr> <mmd_addr>\n"
	        "\t     <reg_addr> [<val>]             read/write MDIO register\n"
		"\tmemdump cm|tx|rx <addr> <len>       dump a mem range\n"
		"\tmeminfo                             show memory info\n"
		"\tmtus [<mtu0>...<mtuN>]              read/write MTU table\n"
		"\tpktsched port <idx> <min> <max>     set TX port scheduler params\n"
		"\tpktsched tunnelq <idx> <max>\n"
		"\t         <binding>                  set TX tunnelq scheduler params\n"
		"\tpktsched tx <idx>\n"
	        "\t         [<param> <val>] ...        set Tx HW scheduler\n"
		"\tpm [<TX page spec> <RX page spec>]  read/write PM config\n"
		"\tproto                               read proto SRAM\n"
		"\tqset                                read qset parameters\n"
		"\tqsets                               read # of qsets\n"
		"\treg <address>[=<val>]               read/write register\n"
		"\tregdump [<module>]                  dump registers\n"
		"\ttcamdump <address> <count>          show TCAM contents\n"
		"\ttcb <index>                         read TCB\n"
		"\ttrace tx|rx|all on|off [not]\n"
	        "\t      [<param> <val>[:<mask>]] ...  write trace parameters\n"
		);
	exit(fp == stderr ? 1 : 0);
}