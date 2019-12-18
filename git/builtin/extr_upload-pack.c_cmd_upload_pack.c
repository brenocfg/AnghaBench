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
struct upload_pack_options {int stateless_rpc; int advertise_refs; int daemon_mode; scalar_t__ timeout; int /*<<< orphan*/  member_0; } ;
struct serve_options {int advertise_capabilities; int stateless_rpc; } ;
struct option {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 int /*<<< orphan*/  N_ (char*) ; 
 struct option OPT_BOOL (int /*<<< orphan*/ ,char*,int*,int /*<<< orphan*/ ) ; 
 struct option OPT_END () ; 
 struct option OPT_INTEGER (int /*<<< orphan*/ ,char*,scalar_t__*,int /*<<< orphan*/ ) ; 
 struct serve_options SERVE_OPTIONS_INIT ; 
 int determine_protocol_version_server () ; 
 int /*<<< orphan*/  die (char*,char const*) ; 
 int /*<<< orphan*/  enter_repo (char const*,int) ; 
 int /*<<< orphan*/  packet_trace_identity (char*) ; 
 int /*<<< orphan*/  packet_write_fmt (int,char*) ; 
 int parse_options (int,char const**,char const*,struct option*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  protocol_unknown_version 131 
#define  protocol_v0 130 
#define  protocol_v1 129 
#define  protocol_v2 128 
 scalar_t__ read_replace_refs ; 
 int /*<<< orphan*/  serve (struct serve_options*) ; 
 int /*<<< orphan*/  setup_path () ; 
 int /*<<< orphan*/  upload_pack (struct upload_pack_options*) ; 
 int /*<<< orphan*/  upload_pack_usage ; 
 int /*<<< orphan*/  usage_with_options (int /*<<< orphan*/ ,struct option*) ; 

int cmd_upload_pack(int argc, const char **argv, const char *prefix)
{
	const char *dir;
	int strict = 0;
	struct upload_pack_options opts = { 0 };
	struct serve_options serve_opts = SERVE_OPTIONS_INIT;
	struct option options[] = {
		OPT_BOOL(0, "stateless-rpc", &opts.stateless_rpc,
			 N_("quit after a single request/response exchange")),
		OPT_BOOL(0, "advertise-refs", &opts.advertise_refs,
			 N_("exit immediately after initial ref advertisement")),
		OPT_BOOL(0, "strict", &strict,
			 N_("do not try <directory>/.git/ if <directory> is no Git directory")),
		OPT_INTEGER(0, "timeout", &opts.timeout,
			    N_("interrupt transfer after <n> seconds of inactivity")),
		OPT_END()
	};

	packet_trace_identity("upload-pack");
	read_replace_refs = 0;

	argc = parse_options(argc, argv, prefix, options, upload_pack_usage, 0);

	if (argc != 1)
		usage_with_options(upload_pack_usage, options);

	if (opts.timeout)
		opts.daemon_mode = 1;

	setup_path();

	dir = argv[0];

	if (!enter_repo(dir, strict))
		die("'%s' does not appear to be a git repository", dir);

	switch (determine_protocol_version_server()) {
	case protocol_v2:
		serve_opts.advertise_capabilities = opts.advertise_refs;
		serve_opts.stateless_rpc = opts.stateless_rpc;
		serve(&serve_opts);
		break;
	case protocol_v1:
		/*
		 * v1 is just the original protocol with a version string,
		 * so just fall through after writing the version string.
		 */
		if (opts.advertise_refs || !opts.stateless_rpc)
			packet_write_fmt(1, "version 1\n");

		/* fallthrough */
	case protocol_v0:
		upload_pack(&opts);
		break;
	case protocol_unknown_version:
		BUG("unknown protocol version");
	}

	return 0;
}