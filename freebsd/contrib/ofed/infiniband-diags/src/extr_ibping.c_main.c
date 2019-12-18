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
typedef  unsigned long long uint64_t ;
struct ibdiag_opt {char* member_0; char member_1; int member_2; char* member_3; char* member_4; } ;
struct TYPE_5__ {int grh_present; int /*<<< orphan*/  gid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IBEXIT (char*,...) ; 
 scalar_t__ IB_DEST_LID ; 
 int IB_SA_CLASS ; 
 int IB_VENDOR_OPENIB_PING_CLASS ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  cl_get_time_stamp () ; 
 int /*<<< orphan*/  count ; 
 int /*<<< orphan*/  dgid ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  flood ; 
 int /*<<< orphan*/  get_host_and_domain (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  host_and_domain ; 
 int /*<<< orphan*/  ibd_ca ; 
 int /*<<< orphan*/  ibd_ca_port ; 
 scalar_t__ ibd_dest_type ; 
 int /*<<< orphan*/  ibd_sm_id ; 
 int /*<<< orphan*/  ibdiag_process_opts (int,char**,int /*<<< orphan*/ *,char*,struct ibdiag_opt const*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ibdiag_show_usage () ; 
 unsigned long long ibping (TYPE_1__*,int /*<<< orphan*/ ) ; 
 char* ibping_serv () ; 
 int /*<<< orphan*/  lost ; 
 scalar_t__ mad_register_client_via (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mad_register_server_via (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mad_rpc_close_port (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mad_rpc_open_port (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 unsigned long long maxrtt ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 unsigned long long minrtt ; 
 int /*<<< orphan*/  ntrans ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  oui ; 
 TYPE_1__ portid ; 
 int /*<<< orphan*/  portid2str (TYPE_1__*) ; 
 int /*<<< orphan*/  process_opt ; 
 int /*<<< orphan*/  replied ; 
 int /*<<< orphan*/  report (int /*<<< orphan*/ ) ; 
 scalar_t__ resolve_portid_str (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ server ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  srcport ; 
 int /*<<< orphan*/  start ; 
 int /*<<< orphan*/  total_rtt ; 
 scalar_t__ with_grh ; 

int main(int argc, char **argv)
{
	int mgmt_classes[1] = { IB_SA_CLASS };
	int ping_class = IB_VENDOR_OPENIB_PING_CLASS;
	uint64_t rtt;
	char *err;

	const struct ibdiag_opt opts[] = {
		{"count", 'c', 1, "<num>", "stop after count packets"},
		{"flood", 'f', 0, NULL, "flood destination"},
		{"oui", 'o', 1, NULL, "use specified OUI number"},
		{"Server", 'S', 0, NULL, "start in server mode"},
		{"dgid", 25, 1, NULL, "remote gid (IPv6 format)"},
		{0}
	};
	char usage_args[] = "<dest lid|guid>";

	ibdiag_process_opts(argc, argv, NULL, "DKy", opts, process_opt,
			    usage_args, NULL);

	argc -= optind;
	argv += optind;

	if (!argc && !server)
		ibdiag_show_usage();

	srcport = mad_rpc_open_port(ibd_ca, ibd_ca_port, mgmt_classes, 1);
	if (!srcport)
		IBEXIT("Failed to open '%s' port '%d'", ibd_ca, ibd_ca_port);

	if (server) {
		if (mad_register_server_via(ping_class, 0, 0, oui, srcport) < 0)
			IBEXIT("can't serve class %d on this port",
				ping_class);

		get_host_and_domain(host_and_domain, sizeof host_and_domain);

		if ((err = ibping_serv()))
			IBEXIT("ibping to %s: %s", portid2str(&portid), err);
		exit(0);
	}

	if (mad_register_client_via(ping_class, 0, srcport) < 0)
		IBEXIT("can't register ping class %d on this port",
			ping_class);

	if (with_grh && ibd_dest_type != IB_DEST_LID)
		IBEXIT("When using GRH, LID should be provided");
	if (resolve_portid_str(ibd_ca, ibd_ca_port, &portid, argv[0],
			       ibd_dest_type, ibd_sm_id, srcport) < 0)
		IBEXIT("can't resolve destination port %s", argv[0]);

	if (with_grh) {
		portid.grh_present = 1;
		memcpy(&portid.gid, &dgid, sizeof(portid.gid));
	}

	signal(SIGINT, report);
	signal(SIGTERM, report);

	start = cl_get_time_stamp();

	while (count-- > 0) {
		ntrans++;
		if ((rtt = ibping(&portid, flood)) == ~0ull) {
			DEBUG("ibping to %s failed", portid2str(&portid));
			lost++;
		} else {
			if (rtt < minrtt)
				minrtt = rtt;
			if (rtt > maxrtt)
				maxrtt = rtt;
			total_rtt += rtt;
			replied++;
		}

		if (!flood)
			sleep(1);
	}

	report(0);

	mad_rpc_close_port(srcport);

	exit(-1);
}