#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  usage_args ;
typedef  scalar_t__ uint16_t ;
struct TYPE_9__ {int /*<<< orphan*/  lid; } ;
struct sa_handle {TYPE_1__ dport; } ;
struct query_params {int reversible; int numb_path; int qos_class; int sl; int proxy_join; int /*<<< orphan*/  cpi; void* dlid; void* slid; int /*<<< orphan*/  sa_dgid; scalar_t__ with_grh; scalar_t__ hop_limit; } ;
struct query_cmd {char* name; char* alias; char* usage; scalar_t__ query_type; int (* handler ) (struct query_cmd const*,struct sa_handle*,struct query_params*,int,char**) ;} ;
struct ibdiag_opt {char* member_0; char member_1; int member_2; char* member_3; char* member_4; } ;
struct TYPE_10__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ ibmad_gid_t ;
struct TYPE_11__ {int /*<<< orphan*/  lid; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ ib_portid_t ;

/* Variables and functions */
 scalar_t__ CLASS_PORT_INFO ; 
 int /*<<< orphan*/  DEFAULT_SA_TIMEOUT_MS ; 
 int EINVAL ; 
 scalar_t__ GUID_ONLY ; 
 int /*<<< orphan*/  IBEXIT (char*) ; 
 int /*<<< orphan*/  IBPANIC (char*) ; 
 scalar_t__ IB_SA_ATTR_NODERECORD ; 
 scalar_t__ IB_SA_ATTR_SWITCHINFORECORD ; 
 scalar_t__ LID_ONLY ; 
 scalar_t__ NAME_OF_GUID ; 
 scalar_t__ NAME_OF_LID ; 
#define  SAQUERY_CMD_CLASS_PORT_INFO 132 
#define  SAQUERY_CMD_ISSM 131 
#define  SAQUERY_CMD_MCGROUPS 130 
#define  SAQUERY_CMD_MCMEMBERS 129 
#define  SAQUERY_CMD_NODE_RECORD 128 
 int SAQUERY_CMD_QUERY ; 
 scalar_t__ UNIQUE_LID_ONLY ; 
 int /*<<< orphan*/  close_node_name_map (int /*<<< orphan*/ ) ; 
 int command ; 
 scalar_t__* dst_lid ; 
 int /*<<< orphan*/  dump_class_port_info (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 
 struct query_cmd* find_query (char*) ; 
 struct query_cmd* find_query_by_type (scalar_t__) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (scalar_t__*) ; 
 void* get_lid (struct sa_handle*,scalar_t__*) ; 
 int /*<<< orphan*/  ibd_ca ; 
 int /*<<< orphan*/  ibd_ca_port ; 
 int /*<<< orphan*/  ibd_timeout ; 
 int /*<<< orphan*/  ibdiag_process_opts (int,char**,struct query_params*,char*,struct ibdiag_opt const*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ibdiag_show_usage () ; 
 int /*<<< orphan*/  memcmp (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct query_params*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  node_name_map ; 
 int /*<<< orphan*/  node_name_map_file ; 
 scalar_t__ node_print_desc ; 
 int ntohs (scalar_t__) ; 
 int /*<<< orphan*/  open_node_name_map (int /*<<< orphan*/ ) ; 
 scalar_t__ optind ; 
 int print_issm_records (struct sa_handle*,struct query_params*) ; 
 int print_multicast_group_records (struct sa_handle*,struct query_params*) ; 
 int print_multicast_member_records (struct sa_handle*,struct query_params*) ; 
 int print_node_records (struct sa_handle*,struct query_params*) ; 
 int /*<<< orphan*/  process_opt ; 
 struct query_cmd* query_cmds ; 
 int query_sa_cpi (struct sa_handle*,struct query_params*) ; 
 scalar_t__ query_type ; 
 scalar_t__ requested_guid ; 
 int /*<<< orphan*/  requested_guid_flag ; 
 scalar_t__ requested_lid ; 
 int /*<<< orphan*/  requested_lid_flag ; 
 char* requested_name ; 
 int resolve_self (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sa_free_handle (struct sa_handle*) ; 
 struct sa_handle* sa_get_handle () ; 
 int sa_set_handle (struct sa_handle*,int,TYPE_2__*) ; 
 int sm_pr_query (struct sa_handle*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ snprintf (char*,int,char*,...) ; 
 int sprintf (char*,char*) ; 
 scalar_t__* src_lid ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int stub1 (struct query_cmd const*,struct sa_handle*,struct query_params*,int,char**) ; 
 int /*<<< orphan*/  umad_done () ; 
 scalar_t__ umad_init () ; 

int main(int argc, char **argv)
{
	ib_portid_t portid = { 0 };
	int port = 0;
	int sa_cpi_required = 0;
	char usage_args[1024];
	struct sa_handle * h;
	struct query_params params;
	const struct query_cmd *q;
	int status;
	int n;

	const struct ibdiag_opt opts[] = {
		{"p", 'p', 0, NULL, "get PathRecord info"},
		{"N", 'N', 0, NULL, "get NodeRecord info"},
		{"L", 'L', 0, NULL, "return the Lids of the name specified"},
		{"l", 'l', 0, NULL,
		 "return the unique Lid of the name specified"},
		{"G", 'G', 0, NULL, "return the Guids of the name specified"},
		{"O", 'O', 0, NULL, "return name for the Lid specified"},
		{"U", 'U', 0, NULL, "return name for the Guid specified"},
		{"s", 's', 0, NULL, "return the PortInfoRecords with isSM or"
		 " isSMdisabled capability mask bit on"},
		{"g", 'g', 0, NULL, "get multicast group info"},
		{"m", 'm', 0, NULL, "get multicast member info (if multicast"
		 " group specified, list member GIDs only for group specified,"
		 " for example 'saquery -m 0xC000')"},
		{"x", 'x', 0, NULL, "get LinkRecord info"},
		{"c", 'c', 0, NULL, "get the SA's class port info"},
		{"S", 'S', 0, NULL, "get ServiceRecord info"},
		{"I", 'I', 0, NULL, "get InformInfoRecord (subscription) info"},
		{"list", 'D', 0, NULL, "the node desc of the CA's"},
		{"with-grh", 23, 0, NULL, "add GRH to path record query"},
		{"sa-dgid", 24, 1, "<gid>",
		 "Set destination GID (in IPv6 format) in the GRH"},
		{"src-to-dst", 1, 1, "<src:dst>", "get a PathRecord for"
		 " <src:dst> where src and dst are either node names or LIDs"},
		{"sgid-to-dgid", 2, 1, "<sgid-dgid>", "get a PathRecord for"
		 " <sgid-dgid> where sgid and dgid are addresses in IPv6 format"},
		{"node-name-map", 3, 1, "<file>",
		 "specify a node name map file"},
		{"smkey", 4, 1, "<val>",
		 "SA SM_Key value for the query."
		 " If non-numeric value (like 'x') is specified then"
		 " saquery will prompt for a value. "
		 " Default (when not specified here or in ibdiag.conf) is to "
		 " use SM_Key == 0 (or \"untrusted\")"},
		{"slid", 5, 1, "<lid>", "Source LID (PathRecord)"},
		{"dlid", 6, 1, "<lid>", "Destination LID (PathRecord)"},
		{"mlid", 7, 1, "<lid>", "Multicast LID (MCMemberRecord)"},
		{"sgid", 14, 1, "<gid>",
		 "Source GID (IPv6 format) (PathRecord)"},
		{"dgid", 15, 1, "<gid>",
		 "Destination GID (IPv6 format) (PathRecord)"},
		{"gid", 16, 1, "<gid>", "Port GID (MCMemberRecord)"},
		{"mgid", 17, 1, "<gid>", "Multicast GID (MCMemberRecord)"},
		{"reversible", 'r', 1, NULL, "Reversible path (PathRecord)"},
		{"numb_path", 'n', 1, NULL, "Number of paths (PathRecord)"},
		{"pkey", 18, 1, NULL, "P_Key (PathRecord, MCMemberRecord)."
		 " If non-numeric value (like 'x') is specified then"
		 " saquery will prompt for a value"},
		{"qos_class", 'Q', 1, NULL, "QoS Class (PathRecord)"},
		{"sl", 19, 1, NULL,
		 "Service level (PathRecord, MCMemberRecord)"},
		{"mtu", 'M', 1, NULL,
		 "MTU and selector (PathRecord, MCMemberRecord)"},
		{"rate", 'R', 1, NULL,
		 "Rate and selector (PathRecord, MCMemberRecord)"},
		{"pkt_lifetime", 20, 1, NULL,
		 "Packet lifetime and selector (PathRecord, MCMemberRecord)"},
		{"qkey", 'q', 1, NULL, "Q_Key (MCMemberRecord)."
		 " If non-numeric value (like 'x') is specified then"
		 " saquery will prompt for a value"},
		{"tclass", 'T', 1, NULL,
		 "Traffic Class (PathRecord, MCMemberRecord)"},
		{"flow_label", 'F', 1, NULL,
		 "Flow Label (PathRecord, MCMemberRecord)"},
		{"hop_limit", 'H', 1, NULL,
		 "Hop limit (PathRecord, MCMemberRecord)"},
		{"scope", 21, 1, NULL, "Scope (MCMemberRecord)"},
		{"join_state", 'J', 1, NULL, "Join state (MCMemberRecord)"},
		{"proxy_join", 'X', 1, NULL, "Proxy join (MCMemberRecord)"},
		{"service_id", 22, 1, NULL, "ServiceID (PathRecord)"},
		{0}
	};

	memset(&params, 0, sizeof params);
	params.hop_limit = 0;
	params.reversible = -1;
	params.numb_path = -1;
	params.qos_class = -1;
	params.sl = -1;
	params.proxy_join = -1;

	n = sprintf(usage_args, "[query-name] [<name> | <lid> | <guid>]\n"
		    "\nSupported query names (and aliases):\n");
	for (q = query_cmds; q->name; q++) {
		n += snprintf(usage_args + n, sizeof(usage_args) - n,
			      "  %s (%s) %s\n", q->name,
			      q->alias ? q->alias : "",
			      q->usage ? q->usage : "");
		if (n >= sizeof(usage_args))
			exit(-1);
	}
	snprintf(usage_args + n, sizeof(usage_args) - n,
		 "\n  Queries node records by default.");

	q = NULL;
	ibd_timeout = DEFAULT_SA_TIMEOUT_MS;

	ibdiag_process_opts(argc, argv, &params, "DGLsy", opts, process_opt,
			    usage_args, NULL);

	argc -= optind;
	argv += optind;

	if (!query_type && command == SAQUERY_CMD_QUERY) {
		if (!argc || !(q = find_query(argv[0])))
			query_type = IB_SA_ATTR_NODERECORD;
		else {
			query_type = q->query_type;
			argc--;
			argv++;
		}
	}

	if (argc) {
		if (node_print_desc == NAME_OF_LID) {
			requested_lid = (uint16_t) strtoul(argv[0], NULL, 0);
			requested_lid_flag++;
		} else if (node_print_desc == NAME_OF_GUID) {
			requested_guid = strtoul(argv[0], NULL, 0);
			requested_guid_flag++;
		} else
			requested_name = argv[0];
	}

	if ((node_print_desc == LID_ONLY ||
	     node_print_desc == UNIQUE_LID_ONLY ||
	     node_print_desc == GUID_ONLY) && !requested_name) {
		fprintf(stderr, "ERROR: name not specified\n");
		ibdiag_show_usage();
	}

	if (node_print_desc == NAME_OF_LID && !requested_lid_flag) {
		fprintf(stderr, "ERROR: lid not specified\n");
		ibdiag_show_usage();
	}

	if (node_print_desc == NAME_OF_GUID && !requested_guid_flag) {
		fprintf(stderr, "ERROR: guid not specified\n");
		ibdiag_show_usage();
	}

	/* Note: lid cannot be 0; see infiniband spec 4.1.3 */
	if (node_print_desc == NAME_OF_LID && !requested_lid) {
		fprintf(stderr, "ERROR: lid invalid\n");
		ibdiag_show_usage();
	}

	if (umad_init())
		IBEXIT("Failed to initialized umad library");
	h = sa_get_handle();
	if (!h)
		IBPANIC("Failed to bind to the SA");

	if (params.with_grh) {
		ibmad_gid_t gid = { 0 };
		/*
		 * If GRH destination GID is not specified, try to get it by
		 * querying the SA.
		 */
		if (!memcmp(&gid, &params.sa_dgid, sizeof(ibmad_gid_t))) {
			if ((status = resolve_self(ibd_ca, ibd_ca_port, &portid,
						   &port, 0)) < 0) {
				fprintf(stderr, "can't resolve self port %s\n",
					argv[0]);
				goto error;
			}
			if ((status = sm_pr_query(h, &gid, portid.lid,
						  h->dport.lid)) > 0) {
				fprintf(stderr,
					"Failed to query SA:PathRecord\n");
				goto error;
			}
		} else
			memcpy(&gid, &params.sa_dgid, sizeof(ibmad_gid_t));

		if ((status = sa_set_handle(h, 1, &gid)) < 0) {
			fprintf(stderr, "Failed to set GRH\n");
			goto error;
		}
	}

	node_name_map = open_node_name_map(node_name_map_file);

	if (src_lid && *src_lid)
		params.slid = get_lid(h, src_lid);
	if (dst_lid && *dst_lid)
		params.dlid = get_lid(h, dst_lid);

	if (command == SAQUERY_CMD_CLASS_PORT_INFO ||
	    query_type == CLASS_PORT_INFO ||
	    query_type == IB_SA_ATTR_SWITCHINFORECORD)
		sa_cpi_required = 1;

	if (sa_cpi_required && (status = query_sa_cpi(h, &params)) != 0) {
		fprintf(stderr, "Failed to query SA:ClassPortInfo\n");
		goto error;
	}

	switch (command) {
	case SAQUERY_CMD_NODE_RECORD:
		status = print_node_records(h, &params);
		break;
	case SAQUERY_CMD_CLASS_PORT_INFO:
		dump_class_port_info(&params.cpi);
		status = 0;
		break;
	case SAQUERY_CMD_ISSM:
		status = print_issm_records(h, &params);
		break;
	case SAQUERY_CMD_MCGROUPS:
		status = print_multicast_group_records(h, &params);
		break;
	case SAQUERY_CMD_MCMEMBERS:
		status = print_multicast_member_records(h, &params);
		break;
	default:
		if ((!q && !(q = find_query_by_type(query_type)))
		    || !q->handler) {
			fprintf(stderr, "Unknown query type %d\n",
				ntohs(query_type));
			status = EINVAL;
		} else
			status = q->handler(q, h, &params, argc, argv);
		break;
	}

error:
	if (src_lid)
		free(src_lid);
	sa_free_handle(h);
	umad_done();
	close_node_name_map(node_name_map);
	return (status);
}