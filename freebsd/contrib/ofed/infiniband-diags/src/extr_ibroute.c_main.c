#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ibdiag_opt {char* member_0; char member_1; int member_2; char* member_3; char* member_4; } ;
struct TYPE_5__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ ib_portid_t ;

/* Variables and functions */
 int /*<<< orphan*/  IBEXIT (char*,char*,...) ; 
 int IB_SA_CLASS ; 
 int IB_SMI_CLASS ; 
 int IB_SMI_DIRECT_CLASS ; 
 int /*<<< orphan*/  close_node_name_map (int /*<<< orphan*/ ) ; 
 char* dump_multicast_tables (TYPE_1__*,unsigned int,unsigned int) ; 
 char* dump_unicast_tables (TYPE_1__*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibd_ca ; 
 int /*<<< orphan*/  ibd_ca_port ; 
 int /*<<< orphan*/  ibd_dest_type ; 
 int /*<<< orphan*/  ibd_mkey ; 
 int /*<<< orphan*/  ibd_sm_id ; 
 int /*<<< orphan*/  ibdiag_process_opts (int,char**,int /*<<< orphan*/ *,char*,struct ibdiag_opt const*,int /*<<< orphan*/ ,char*,char const**) ; 
 int /*<<< orphan*/  ibdiag_show_usage () ; 
 int /*<<< orphan*/  mad_rpc_close_port (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mad_rpc_open_port (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ multicast ; 
 int /*<<< orphan*/  node_name_map ; 
 int /*<<< orphan*/  node_name_map_file ; 
 int /*<<< orphan*/  open_node_name_map (int /*<<< orphan*/ ) ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  process_opt ; 
 scalar_t__ resolve_portid_str (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mkey_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srcport ; 
 unsigned int strtoul (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int main(int argc, char **argv)
{
	int mgmt_classes[3] =
	    { IB_SMI_CLASS, IB_SMI_DIRECT_CLASS, IB_SA_CLASS };
	ib_portid_t portid = { 0 };
	unsigned startlid = 0, endlid = 0;
	char *err;

	const struct ibdiag_opt opts[] = {
		{"all", 'a', 0, NULL, "show all lids, even invalid entries"},
		{"no_dests", 'n', 0, NULL,
		 "do not try to resolve destinations"},
		{"Multicast", 'M', 0, NULL, "show multicast forwarding tables"},
		{"node-name-map", 1, 1, "<file>", "node name map file"},
		{0}
	};
	char usage_args[] = "[<dest dr_path|lid|guid> [<startlid> [<endlid>]]]";
	const char *usage_examples[] = {
		" -- Unicast examples:",
		"4\t# dump all lids with valid out ports of switch with lid 4",
		"-a 4\t# same, but dump all lids, even with invalid out ports",
		"-n 4\t# simple dump format - no destination resolving",
		"4 10\t# dump lids starting from 10",
		"4 0x10 0x20\t# dump lid range",
		"-G 0x08f1040023\t# resolve switch by GUID",
		"-D 0,1\t# resolve switch by direct path",
		" -- Multicast examples:",
		"-M 4\t# dump all non empty mlids of switch with lid 4",
		"-M 4 0xc010 0xc020\t# same, but with range",
		"-M -n 4\t# simple dump format",
		NULL,
	};

	ibdiag_process_opts(argc, argv, NULL, "K", opts, process_opt,
			    usage_args, usage_examples);

	argc -= optind;
	argv += optind;

	if (!argc)
		ibdiag_show_usage();

	if (argc > 1)
		startlid = strtoul(argv[1], 0, 0);
	if (argc > 2)
		endlid = strtoul(argv[2], 0, 0);

	node_name_map = open_node_name_map(node_name_map_file);

	srcport = mad_rpc_open_port(ibd_ca, ibd_ca_port, mgmt_classes, 3);
	if (!srcport)
		IBEXIT("Failed to open '%s' port '%d'", ibd_ca, ibd_ca_port);

	smp_mkey_set(srcport, ibd_mkey);

	if (resolve_portid_str(ibd_ca, ibd_ca_port, &portid, argv[0],
			       ibd_dest_type, ibd_sm_id, srcport) < 0)
		IBEXIT("can't resolve destination port %s", argv[0]);

	if (multicast)
		err = dump_multicast_tables(&portid, startlid, endlid);
	else
		err = dump_unicast_tables(&portid, startlid, endlid);

	if (err)
		IBEXIT("dump tables: %s", err);

	mad_rpc_close_port(srcport);
	close_node_name_map(node_name_map);
	exit(0);
}