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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 char* progname ; 

__attribute__((used)) static void
usage(FILE *fp)
{
	fprintf(fp, "Usage: %s <nexus> [operation]\n", progname);
	fprintf(fp,
	    "\tclearstats <port>                   clear port statistics\n"
	    "\tcontext <type> <id>                 show an SGE context\n"
	    "\tdumpstate <dump.bin>                dump chip state\n"
	    "\tfilter <idx> [<param> <val>] ...    set a filter\n"
	    "\tfilter <idx> delete|clear [prio 1]  delete a filter\n"
	    "\tfilter list                         list all filters\n"
	    "\tfilter mode [<match>] ...           get/set global filter mode\n"
	    "\thashfilter [<param> <val>] ...      set a hashfilter\n"
	    "\thashfilter <idx> delete|clear       delete a hashfilter\n"
	    "\thashfilter list                     list all hashfilters\n"
	    "\thashfilter mode                     get global hashfilter mode\n"
	    "\ti2c <port> <devaddr> <addr> [<len>] read from i2c device\n"
	    "\tloadboot <bi.bin> [pf|offset <val>] install boot image\n"
	    "\tloadboot clear [pf|offset <val>]    remove boot image\n"
	    "\tloadboot-cfg <bc.bin>               install boot config\n"
	    "\tloadboot-cfg clear                  remove boot config\n"
	    "\tloadcfg <fw-config.txt>             install configuration file\n"
	    "\tloadcfg clear                       remove configuration file\n"
	    "\tloadfw <fw-image.bin>               install firmware\n"
	    "\tmemdump <addr> <len>                dump a memory range\n"
	    "\tmodinfo <port> [raw]                optics/cable information\n"
	    "\tpolicy <policy.txt>                 install offload policy\n"
	    "\tpolicy clear                        remove offload policy\n"
	    "\treg <address>[=<val>]               read/write register\n"
	    "\treg64 <address>[=<val>]             read/write 64 bit register\n"
	    "\tregdump [<module>] ...              dump registers\n"
	    "\tsched-class params <param> <val> .. configure TX scheduler class\n"
	    "\tsched-queue <port> <queue> <class>  bind NIC queues to TX Scheduling class\n"
	    "\tstdio                               interactive mode\n"
	    "\ttcb <tid>                           read TCB\n"
	    "\ttracer <idx> tx<n>|rx<n>            set and enable a tracer\n"
	    "\ttracer <idx> disable|enable         disable or enable a tracer\n"
	    "\ttracer list                         list all tracers\n"
	    );
}