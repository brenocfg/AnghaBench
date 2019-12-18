#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct ibdiag_opt {char* member_0; float member_1; int member_2; char* member_3; char* member_4; } ;
struct TYPE_9__ {scalar_t__ lid; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ ib_portid_t ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/  IBEXIT (char*,...) ; 
 int /*<<< orphan*/  IBWARN (char*) ; 
 scalar_t__ IB_DEST_DRPATH ; 
 int IB_SA_CLASS ; 
 int IB_SMI_CLASS ; 
 int IB_SMI_DIRECT_CLASS ; 
 int /*<<< orphan*/  close_node_name_map (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_mcpath (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dumplevel ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f ; 
 int /*<<< orphan*/ * find_mcpath (TYPE_1__*,int) ; 
 scalar_t__ find_route (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_target_portguid (TYPE_1__*) ; 
 int /*<<< orphan*/  ibd_ca ; 
 int /*<<< orphan*/  ibd_ca_port ; 
 scalar_t__ ibd_dest_type ; 
 int /*<<< orphan*/  ibd_mkey ; 
 int /*<<< orphan*/  ibd_sm_id ; 
 scalar_t__ ibd_timeout ; 
 int /*<<< orphan*/  ibdiag_process_opts (int,char**,int /*<<< orphan*/ *,char*,struct ibdiag_opt const*,int /*<<< orphan*/ ,char*,char const**) ; 
 int /*<<< orphan*/  ibdiag_show_usage () ; 
 int /*<<< orphan*/  mad_rpc_close_port (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mad_rpc_open_port (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int mlid ; 
 int /*<<< orphan*/  multicast ; 
 int /*<<< orphan*/  node_name_map ; 
 int /*<<< orphan*/  node_name_map_file ; 
 int /*<<< orphan*/  open_node_name_map (int /*<<< orphan*/ ) ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  portid2str (TYPE_1__*) ; 
 int /*<<< orphan*/  process_opt ; 
 scalar_t__ resolve_lid (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ resolve_portid_str (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mkey_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srcport ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  target_portguid ; 
 scalar_t__ timeout ; 

int main(int argc, char **argv)
{
	int mgmt_classes[3] =
	    { IB_SMI_CLASS, IB_SMI_DIRECT_CLASS, IB_SA_CLASS };
	ib_portid_t my_portid = { 0 };
	ib_portid_t src_portid = { 0 };
	ib_portid_t dest_portid = { 0 };
	Node *endnode;

	const struct ibdiag_opt opts[] = {
		{"force", 'f', 0, NULL, "force"},
		{"no_info", 'n', 0, NULL, "simple format"},
		{"mlid", 'm', 1, "<mlid>", "multicast trace of the mlid"},
		{"node-name-map", 1, 1, "<file>", "node name map file"},
		{0}
	};
	char usage_args[] = "<src-addr> <dest-addr>";
	const char *usage_examples[] = {
		"- Unicast examples:",
		"4 16\t\t\t# show path between lids 4 and 16",
		"-n 4 16\t\t# same, but using simple output format",
		"-G 0x8f1040396522d 0x002c9000100d051\t# use guid addresses",

		" - Multicast examples:",
		"-m 0xc000 4 16\t# show multicast path of mlid 0xc000 between lids 4 and 16",
		NULL,
	};

	ibdiag_process_opts(argc, argv, NULL, "DK", opts, process_opt,
			    usage_args, usage_examples);

	f = stdout;
	argc -= optind;
	argv += optind;

	if (argc < 2)
		ibdiag_show_usage();

	if (ibd_timeout)
		timeout = ibd_timeout;

	srcport = mad_rpc_open_port(ibd_ca, ibd_ca_port, mgmt_classes, 3);
	if (!srcport)
		IBEXIT("Failed to open '%s' port '%d'", ibd_ca, ibd_ca_port);

	smp_mkey_set(srcport, ibd_mkey);

	node_name_map = open_node_name_map(node_name_map_file);

	if (resolve_portid_str(ibd_ca, ibd_ca_port, &src_portid, argv[0],
			       ibd_dest_type, ibd_sm_id, srcport) < 0)
		IBEXIT("can't resolve source port %s", argv[0]);

	if (resolve_portid_str(ibd_ca, ibd_ca_port, &dest_portid, argv[1],
			       ibd_dest_type, ibd_sm_id, srcport) < 0)
		IBEXIT("can't resolve destination port %s", argv[1]);

	if (ibd_dest_type == IB_DEST_DRPATH) {
		if (resolve_lid(&src_portid, NULL) < 0)
			IBEXIT("cannot resolve lid for port \'%s\'",
				portid2str(&src_portid));
		if (resolve_lid(&dest_portid, NULL) < 0)
			IBEXIT("cannot resolve lid for port \'%s\'",
				portid2str(&dest_portid));
	}

	if (dest_portid.lid == 0 || src_portid.lid == 0) {
		IBWARN("bad src/dest lid");
		ibdiag_show_usage();
	}

	if (ibd_dest_type != IB_DEST_DRPATH) {
		/* first find a direct path to the src port */
		if (find_route(&my_portid, &src_portid, 0) < 0)
			IBEXIT("can't find a route to the src port");

		src_portid = my_portid;
	}

	if (!multicast) {
		if (find_route(&src_portid, &dest_portid, dumplevel) < 0)
			IBEXIT("can't find a route from src to dest");
		exit(0);
	} else {
		if (mlid < 0xc000)
			IBWARN("invalid MLID; must be 0xc000 or larger");
	}

	if (!(target_portguid = find_target_portguid(&dest_portid)))
		IBEXIT("can't reach target lid %d", dest_portid.lid);

	if (!(endnode = find_mcpath(&src_portid, mlid)))
		IBEXIT("can't find a multicast route from src to dest");

	/* dump multicast path */
	dump_mcpath(endnode, dumplevel);

	close_node_name_map(node_name_map);

	mad_rpc_close_port(srcport);

	exit(0);
}