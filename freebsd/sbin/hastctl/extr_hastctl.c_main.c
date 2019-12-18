#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nv {int dummy; } ;
typedef  scalar_t__ int64_t ;
struct TYPE_3__ {int /*<<< orphan*/  hc_controladdr; } ;

/* Variables and functions */
#define  CMD_CREATE 132 
#define  CMD_DUMP 131 
#define  CMD_LIST 130 
#define  CMD_ROLE 129 
#define  CMD_STATUS 128 
 int EX_CONFIG ; 
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  EX_SOFTWARE ; 
 int /*<<< orphan*/  EX_UNAVAILABLE ; 
 int /*<<< orphan*/  EX_USAGE ; 
 int /*<<< orphan*/  HASTCTL_CMD_SETROLE ; 
 int /*<<< orphan*/  HASTCTL_CMD_STATUS ; 
 int /*<<< orphan*/  HAST_ROLE_INIT ; 
 int /*<<< orphan*/  HAST_ROLE_PRIMARY ; 
 int /*<<< orphan*/  HAST_ROLE_SECONDARY ; 
 int /*<<< orphan*/  HAST_TIMEOUT ; 
 int /*<<< orphan*/  PJDLOG_ABORT (char*) ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PJDLOG_MODE_STD ; 
 TYPE_1__* cfg ; 
 int /*<<< orphan*/  cfgpath ; 
 int /*<<< orphan*/  control_create (int,char**,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  control_dump (int,char**) ; 
 int control_list (struct nv*) ; 
 int control_set_role (struct nv*,char*) ; 
 int control_status (struct nv*) ; 
 int /*<<< orphan*/  controlconn ; 
 scalar_t__ drop_privs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int expand_number (int /*<<< orphan*/ ,scalar_t__*) ; 
 int getopt (int,char**,char const*) ; 
 int hast_proto_recv_hdr (int /*<<< orphan*/ ,struct nv**) ; 
 int hast_proto_send (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct nv*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv_add_string (struct nv*,char*,char*,int) ; 
 int /*<<< orphan*/  nv_add_uint8 (struct nv*,int /*<<< orphan*/ ,char*) ; 
 struct nv* nv_alloc () ; 
 int /*<<< orphan*/  nv_free (struct nv*) ; 
 int nv_get_int16 (struct nv*,char*) ; 
 int /*<<< orphan*/  nv_set_error (struct nv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  pjdlog_debug_set (int) ; 
 int /*<<< orphan*/  pjdlog_exit (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pjdlog_exitx (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  pjdlog_init (int /*<<< orphan*/ ) ; 
 int proto_client (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int proto_connect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  usage () ; 
 TYPE_1__* yy_config_parse (int /*<<< orphan*/ ,int) ; 

int
main(int argc, char *argv[])
{
	struct nv *nv;
	int64_t mediasize, extentsize, keepdirty;
	int cmd, debug, error, ii;
	const char *optstr;

	debug = 0;
	mediasize = extentsize = keepdirty = 0;

	if (argc == 1)
		usage();

	if (strcmp(argv[1], "create") == 0) {
		cmd = CMD_CREATE;
		optstr = "c:de:k:m:h";
	} else if (strcmp(argv[1], "role") == 0) {
		cmd = CMD_ROLE;
		optstr = "c:dh";
	} else if (strcmp(argv[1], "list") == 0) {
		cmd = CMD_LIST;
		optstr = "c:dh";
	} else if (strcmp(argv[1], "status") == 0) {
		cmd = CMD_STATUS;
		optstr = "c:dh";
	} else if (strcmp(argv[1], "dump") == 0) {
		cmd = CMD_DUMP;
		optstr = "c:dh";
	} else
		usage();

	argc--;
	argv++;

	for (;;) {
		int ch;

		ch = getopt(argc, argv, optstr);
		if (ch == -1)
			break;
		switch (ch) {
		case 'c':
			cfgpath = optarg;
			break;
		case 'd':
			debug++;
			break;
		case 'e':
			if (expand_number(optarg, &extentsize) == -1)
				errx(EX_USAGE, "Invalid extentsize");
			break;
		case 'k':
			if (expand_number(optarg, &keepdirty) == -1)
				errx(EX_USAGE, "Invalid keepdirty");
			break;
		case 'm':
			if (expand_number(optarg, &mediasize) == -1)
				errx(EX_USAGE, "Invalid mediasize");
			break;
		case 'h':
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;

	switch (cmd) {
	case CMD_CREATE:
	case CMD_ROLE:
		if (argc == 0)
			usage();
		break;
	}

	pjdlog_init(PJDLOG_MODE_STD);
	pjdlog_debug_set(debug);

	cfg = yy_config_parse(cfgpath, true);
	PJDLOG_ASSERT(cfg != NULL);

	switch (cmd) {
	case CMD_CREATE:
		control_create(argc, argv, mediasize, extentsize, keepdirty);
		/* NOTREACHED */
		PJDLOG_ABORT("What are we doing here?!");
		break;
	case CMD_DUMP:
		/* Dump metadata from local component of the given resource. */
		control_dump(argc, argv);
		/* NOTREACHED */
		PJDLOG_ABORT("What are we doing here?!");
		break;
	case CMD_ROLE:
		/* Change role for the given resources. */
		if (argc < 2)
			usage();
		nv = nv_alloc();
		nv_add_uint8(nv, HASTCTL_CMD_SETROLE, "cmd");
		if (strcmp(argv[0], "init") == 0)
			nv_add_uint8(nv, HAST_ROLE_INIT, "role");
		else if (strcmp(argv[0], "primary") == 0)
			nv_add_uint8(nv, HAST_ROLE_PRIMARY, "role");
		else if (strcmp(argv[0], "secondary") == 0)
			nv_add_uint8(nv, HAST_ROLE_SECONDARY, "role");
		else
			usage();
		for (ii = 0; ii < argc - 1; ii++)
			nv_add_string(nv, argv[ii + 1], "resource%d", ii);
		break;
	case CMD_LIST:
	case CMD_STATUS:
		/* Obtain status of the given resources. */
		nv = nv_alloc();
		nv_add_uint8(nv, HASTCTL_CMD_STATUS, "cmd");
		if (argc == 0)
			nv_add_string(nv, "all", "resource%d", 0);
		else {
			for (ii = 0; ii < argc; ii++)
				nv_add_string(nv, argv[ii], "resource%d", ii);
		}
		break;
	default:
		PJDLOG_ABORT("Impossible command!");
	}

	/* Setup control connection... */
	if (proto_client(NULL, cfg->hc_controladdr, &controlconn) == -1) {
		pjdlog_exit(EX_OSERR,
		    "Unable to setup control connection to %s",
		    cfg->hc_controladdr);
	}
	/* ...and connect to hastd. */
	if (proto_connect(controlconn, HAST_TIMEOUT) == -1) {
		pjdlog_exit(EX_OSERR, "Unable to connect to hastd via %s",
		    cfg->hc_controladdr);
	}

	if (drop_privs(NULL) != 0)
		exit(EX_CONFIG);

	/* Send the command to the server... */
	if (hast_proto_send(NULL, controlconn, nv, NULL, 0) == -1) {
		pjdlog_exit(EX_UNAVAILABLE,
		    "Unable to send command to hastd via %s",
		    cfg->hc_controladdr);
	}
	nv_free(nv);
	/* ...and receive reply. */
	if (hast_proto_recv_hdr(controlconn, &nv) == -1) {
		pjdlog_exit(EX_UNAVAILABLE,
		    "cannot receive reply from hastd via %s",
		    cfg->hc_controladdr);
	}

	error = nv_get_int16(nv, "error");
	if (error != 0) {
		pjdlog_exitx(EX_SOFTWARE, "Error %d received from hastd.",
		    error);
	}
	nv_set_error(nv, 0);

	switch (cmd) {
	case CMD_ROLE:
		error = control_set_role(nv, argv[0]);
		break;
	case CMD_LIST:
		error = control_list(nv);
		break;
	case CMD_STATUS:
		error = control_status(nv);
		break;
	default:
		PJDLOG_ABORT("Impossible command!");
	}

	exit(error);
}