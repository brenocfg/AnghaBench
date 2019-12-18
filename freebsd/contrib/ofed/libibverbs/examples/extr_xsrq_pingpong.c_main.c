#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct option {char* name; int has_arg; char val; } ;
struct ibv_wc {int status; int /*<<< orphan*/  qp_num; } ;
struct TYPE_4__ {int num_clients; int num_tests; int use_event; int /*<<< orphan*/  recv_cq; int /*<<< orphan*/  send_cq; TYPE_1__* rem_dest; void* gidx; void* sl; int /*<<< orphan*/  mtu; void* size; void* ib_port; } ;
struct TYPE_3__ {int pp_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  _SC_PAGESIZE ; 
 TYPE_2__ ctx ; 
 int find_qp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ get_cq_event () ; 
 int getopt_long (int,char**,char*,struct option*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ibv_ack_cq_events (int /*<<< orphan*/ ,int) ; 
 int ibv_poll_cq (int /*<<< orphan*/ ,int,struct ibv_wc*) ; 
 int /*<<< orphan*/  init () ; 
 char* optarg ; 
 int optind ; 
 int /*<<< orphan*/  page_size ; 
 scalar_t__ pp_client_connect (char*,int) ; 
 scalar_t__ pp_client_termination () ; 
 scalar_t__ pp_close_ctx () ; 
 scalar_t__ pp_init_ctx (char*) ; 
 int /*<<< orphan*/  pp_mtu_to_enum (void*) ; 
 scalar_t__ pp_post_recv (int) ; 
 int /*<<< orphan*/  pp_post_send (int) ; 
 scalar_t__ pp_server_connect (int) ; 
 scalar_t__ pp_server_termination () ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strdupa (char*) ; 
 void* strtol (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysconf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage (char*) ; 

int main(int argc, char *argv[])
{
	char          *ib_devname = NULL;
	char          *servername = NULL;
	int           port = 18515;
	int           i, total, cnt = 0;
	int           ne, qpi, num_cq_events = 0;
	struct ibv_wc wc;

	init();
	while (1) {
		int c;

		static struct option long_options[] = {
			{ .name = "port",      .has_arg = 1, .val = 'p' },
			{ .name = "ib-dev",    .has_arg = 1, .val = 'd' },
			{ .name = "ib-port",   .has_arg = 1, .val = 'i' },
			{ .name = "size",      .has_arg = 1, .val = 's' },
			{ .name = "mtu",       .has_arg = 1, .val = 'm' },
			{ .name = "clients",   .has_arg = 1, .val = 'c' },
			{ .name = "num_tests", .has_arg = 1, .val = 'n' },
			{ .name = "sl",        .has_arg = 1, .val = 'l' },
			{ .name = "events",    .has_arg = 0, .val = 'e' },
			{ .name = "gid-idx",   .has_arg = 1, .val = 'g' },
			{}
		};

		c = getopt_long(argc, argv, "p:d:i:s:m:c:n:l:eg:", long_options,
				NULL);
		if (c == -1)
			break;

		switch (c) {
		case 'p':
			port = strtol(optarg, NULL, 0);
			if (port < 0 || port > 65535) {
				usage(argv[0]);
				return 1;
			}
			break;
		case 'd':
			ib_devname = strdupa(optarg);
			break;
		case 'i':
			ctx.ib_port = strtol(optarg, NULL, 0);
			if (ctx.ib_port < 0) {
				usage(argv[0]);
				return 1;
			}
			break;
		case 's':
			ctx.size = strtol(optarg, NULL, 0);
			break;
		case 'm':
			ctx.mtu = pp_mtu_to_enum(strtol(optarg, NULL, 0));
			if (ctx.mtu == 0) {
				usage(argv[0]);
				return 1;
			}
			break;
		case 'c':
			ctx.num_clients = strtol(optarg, NULL, 0);
			break;
		case 'n':
			ctx.num_tests = strtol(optarg, NULL, 0);
			break;
		case 'l':
			ctx.sl = strtol(optarg, NULL, 0);
			break;
		case 'g':
			ctx.gidx = strtol(optarg, NULL, 0);
			break;
		case 'e':
			ctx.use_event = 1;
			break;
		default:
			usage(argv[0]);
			return 1;
		}
	}

	if (optind == argc - 1) {
		servername = strdupa(argv[optind]);
		ctx.num_clients = 1;
	} else if (optind < argc) {
		usage(argv[0]);
		return 1;
	}

	page_size = sysconf(_SC_PAGESIZE);

	if (pp_init_ctx(ib_devname))
		return 1;

	if (pp_post_recv(ctx.num_clients)) {
		fprintf(stderr, "Couldn't post receives\n");
		return 1;
	}

	if (servername) {
		if (pp_client_connect(servername, port))
			return 1;
	} else {
		if (pp_server_connect(port))
			return 1;

		for (i = 0; i < ctx.num_clients; i++)
			pp_post_send(i);
	}

	total = ctx.num_clients * ctx.num_tests;
	while (cnt < total) {
		if (ctx.use_event) {
			if (get_cq_event())
				return 1;

			++num_cq_events;
		}

		do {
			ne = ibv_poll_cq(ctx.recv_cq, 1, &wc);
			if (ne < 0) {
				fprintf(stderr, "Error polling cq %d\n", ne);
				return 1;
			} else if (ne == 0) {
				break;
			}

			if (wc.status) {
				fprintf(stderr, "Work completion error %d\n", wc.status);
				return 1;
			}

			pp_post_recv(ne);
			qpi = find_qp(wc.qp_num);
			if (ctx.rem_dest[qpi].pp_cnt < ctx.num_tests)
				pp_post_send(qpi);
			cnt += ne;
		} while (ne > 0);
	}

	for (cnt = 0; cnt < ctx.num_clients; cnt += ne) {
		ne = ibv_poll_cq(ctx.send_cq, 1, &wc);
		if (ne < 0) {
			fprintf(stderr, "Error polling cq %d\n", ne);
			return 1;
		}
	}

	if (ctx.use_event)
		ibv_ack_cq_events(ctx.recv_cq, num_cq_events);

	/* Process should get an ack from the daemon to close its resources to
	  * make sure latest daemon's response sent via its target QP destined
	  * to an XSRQ created by another client won't be lost.
	  * Failure to do so may cause the other client to wait for that sent
	  * message forever. See comment on pp_post_send.
	*/
	if (servername) {
		if (pp_client_termination())
			return 1;
	} else if (pp_server_termination()) {
		return 1;
	}

	if (pp_close_ctx())
		return 1;

	printf("success\n");
	return 0;
}