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
struct ibnd_config {int /*<<< orphan*/  mkey; int /*<<< orphan*/  flags; scalar_t__ timeout_ms; int /*<<< orphan*/  member_0; } ;
struct ibdiag_opt {char* member_0; char member_1; int member_2; char* member_3; char* member_4; } ;
typedef  int /*<<< orphan*/  ibnd_fabric_t ;

/* Variables and functions */
 int /*<<< orphan*/  IB_NODE_SWITCH ; 
 int IB_SA_CLASS ; 
 int IB_SMI_CLASS ; 
 int IB_SMI_DIRECT_CLASS ; 
 int /*<<< orphan*/  close_node_name_map (int /*<<< orphan*/ ) ; 
 void* endlid ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* ibd_ca ; 
 int ibd_ca_port ; 
 int /*<<< orphan*/  ibd_ibnetdisc_flags ; 
 int /*<<< orphan*/  ibd_mkey ; 
 scalar_t__ ibd_timeout ; 
 int /*<<< orphan*/  ibdiag_process_opts (int,char**,struct ibnd_config*,char*,struct ibdiag_opt const*,int /*<<< orphan*/ ,char*,char const**) ; 
 int /*<<< orphan*/  ibnd_destroy_fabric (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ibnd_discover_fabric (char*,int,int /*<<< orphan*/ *,struct ibnd_config*) ; 
 int /*<<< orphan*/  ibnd_iter_nodes_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mad_rpc_close_port (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mad_rpc_open_port (char*,int,int*,int) ; 
 int /*<<< orphan*/  mad_rpc_set_timeout (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  node_name_map ; 
 int /*<<< orphan*/  node_name_map_file ; 
 int /*<<< orphan*/  open_node_name_map (int /*<<< orphan*/ ) ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  process_opt ; 
 int /*<<< orphan*/  process_switch ; 
 int /*<<< orphan*/  smp_mkey_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srcport ; 
 void* startlid ; 
 int /*<<< orphan*/  stderr ; 
 void* strtoul (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int main(int argc, char **argv)
{
	int rc = 0;
	int mgmt_classes[3] =
	    { IB_SMI_CLASS, IB_SMI_DIRECT_CLASS, IB_SA_CLASS };

	struct ibnd_config config = { 0 };
	ibnd_fabric_t *fabric = NULL;

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
		"-a\t# same, but dump all lids, even with invalid out ports",
		"-n\t# simple dump format - no destination resolving",
		"10\t# dump lids starting from 10",
		"0x10 0x20\t# dump lid range",
		" -- Multicast examples:",
		"-M\t# dump all non empty mlids of switch with lid 4",
		"-M 0xc010 0xc020\t# same, but with range",
		"-M -n\t# simple dump format",
		NULL,
	};

	ibdiag_process_opts(argc, argv, &config, "KGDLs", opts, process_opt,
			    usage_args, usage_examples);

	argc -= optind;
	argv += optind;

	if (argc > 0)
		startlid = strtoul(argv[0], 0, 0);
	if (argc > 1)
		endlid = strtoul(argv[1], 0, 0);

	node_name_map = open_node_name_map(node_name_map_file);

	if (ibd_timeout)
		config.timeout_ms = ibd_timeout;

	config.flags = ibd_ibnetdisc_flags;
	config.mkey = ibd_mkey;

	if ((fabric = ibnd_discover_fabric(ibd_ca, ibd_ca_port, NULL,
						&config)) != NULL) {

		srcport = mad_rpc_open_port(ibd_ca, ibd_ca_port, mgmt_classes, 3);
		if (!srcport) {
			fprintf(stderr,
				"Failed to open '%s' port '%d'\n", ibd_ca, ibd_ca_port);
			rc = -1;
			goto Exit;
		}
		smp_mkey_set(srcport, ibd_mkey);

		if (ibd_timeout) {
			mad_rpc_set_timeout(srcport, ibd_timeout);
		}

		ibnd_iter_nodes_type(fabric, process_switch, IB_NODE_SWITCH, fabric);

		mad_rpc_close_port(srcport);

	} else {
		fprintf(stderr, "Failed to discover fabric\n");
		rc = -1;
	}
Exit:
	ibnd_destroy_fabric(fabric);

	close_node_name_map(node_name_map);
	exit(rc);
}