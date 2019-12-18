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
struct ibdiag_opt {char* member_0; float member_1; int member_2; char* member_3; char* member_4; } ;
typedef  int /*<<< orphan*/  ibnd_fabric_t ;

/* Variables and functions */
 int /*<<< orphan*/  IBEXIT (char*,...) ; 
 scalar_t__ cache_file ; 
 int /*<<< orphan*/  close_node_name_map (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  diff (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ diff_cache_file ; 
 int /*<<< orphan*/  dump_ports_report ; 
 int /*<<< orphan*/  dump_topology (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f ; 
 int /*<<< orphan*/  fopen (char*,char*) ; 
 int /*<<< orphan*/  group ; 
 int /*<<< orphan*/  ibd_ca ; 
 int /*<<< orphan*/  ibd_ca_port ; 
 int /*<<< orphan*/  ibd_ibnetdisc_flags ; 
 int /*<<< orphan*/  ibd_mkey ; 
 scalar_t__ ibd_timeout ; 
 int /*<<< orphan*/  ibdiag_process_opts (int,char**,struct ibnd_config*,char*,struct ibdiag_opt const*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ ibnd_cache_fabric (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ibnd_destroy_fabric (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ibnd_discover_fabric (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ibnd_config*) ; 
 int /*<<< orphan*/  ibnd_iter_nodes (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ibnd_load_fabric (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ list ; 
 int /*<<< orphan*/  list_nodes (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ load_cache_file ; 
 int /*<<< orphan*/  node_name_map ; 
 int /*<<< orphan*/  node_name_map_file ; 
 int /*<<< orphan*/  open_node_name_map (int /*<<< orphan*/ ) ; 
 scalar_t__ optind ; 
 scalar_t__ ports_report ; 
 int /*<<< orphan*/  process_opt ; 
 int /*<<< orphan*/  stdout ; 

int main(int argc, char **argv)
{
	struct ibnd_config config = { 0 };
	ibnd_fabric_t *fabric = NULL;
	ibnd_fabric_t *diff_fabric = NULL;

	const struct ibdiag_opt opts[] = {
		{"full", 'f', 0, NULL, "show full information (ports' speed and width, vlcap)"},
		{"show", 's', 0, NULL, "show more information"},
		{"list", 'l', 0, NULL, "list of connected nodes"},
		{"grouping", 'g', 0, NULL, "show grouping"},
		{"Hca_list", 'H', 0, NULL, "list of connected CAs"},
		{"Switch_list", 'S', 0, NULL, "list of connected switches"},
		{"Router_list", 'R', 0, NULL, "list of connected routers"},
		{"node-name-map", 1, 1, "<file>", "node name map file"},
		{"cache", 2, 1, "<file>",
		 "filename to cache ibnetdiscover data to"},
		{"load-cache", 3, 1, "<file>",
		 "filename of ibnetdiscover cache to load"},
		{"diff", 4, 1, "<file>",
		 "filename of ibnetdiscover cache to diff"},
		{"diffcheck", 5, 1, "<key(s)>",
		 "specify checks to execute for --diff"},
		{"ports", 'p', 0, NULL, "obtain a ports report"},
		{"max_hops", 'm', 0, NULL,
		 "report max hops discovered by the library"},
		{"outstanding_smps", 'o', 1, NULL,
		 "specify the number of outstanding SMP's which should be "
		 "issued during the scan"},
		{0}
	};
	char usage_args[] = "[topology-file]";

	ibdiag_process_opts(argc, argv, &config, "DGKLs", opts, process_opt,
			    usage_args, NULL);

	f = stdout;

	argc -= optind;
	argv += optind;

	if (ibd_timeout)
		config.timeout_ms = ibd_timeout;

	config.flags = ibd_ibnetdisc_flags;

	if (argc && !(f = fopen(argv[0], "w")))
		IBEXIT("can't open file %s for writing", argv[0]);

	config.mkey = ibd_mkey;

	node_name_map = open_node_name_map(node_name_map_file);

	if (diff_cache_file &&
	    !(diff_fabric = ibnd_load_fabric(diff_cache_file, 0)))
		IBEXIT("loading cached fabric for diff failed\n");

	if (load_cache_file) {
		if ((fabric = ibnd_load_fabric(load_cache_file, 0)) == NULL)
			IBEXIT("loading cached fabric failed\n");
	} else {
		if ((fabric =
		     ibnd_discover_fabric(ibd_ca, ibd_ca_port, NULL, &config)) == NULL)
			IBEXIT("discover failed\n");
	}

	if (ports_report)
		ibnd_iter_nodes(fabric, dump_ports_report, NULL);
	else if (list)
		list_nodes(fabric, list);
	else if (diff_fabric)
		diff(diff_fabric, fabric);
	else
		dump_topology(group, fabric);

	if (cache_file)
		if (ibnd_cache_fabric(fabric, cache_file, 0) < 0)
			IBEXIT("caching ibnetdiscover data failed\n");

	ibnd_destroy_fabric(fabric);
	if (diff_fabric)
		ibnd_destroy_fabric(diff_fabric);
	close_node_name_map(node_name_map);
	exit(0);
}