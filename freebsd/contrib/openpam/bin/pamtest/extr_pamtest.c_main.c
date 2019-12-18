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
typedef  int /*<<< orphan*/  hostname ;

/* Variables and functions */
 long INT_MAX ; 
 int /*<<< orphan*/  OPENPAM_RESTRICT_MODULE_NAME ; 
 int /*<<< orphan*/  OPENPAM_RESTRICT_SERVICE_NAME ; 
 int /*<<< orphan*/  OPENPAM_VERIFY_MODULE_FILE ; 
 int /*<<< orphan*/  OPENPAM_VERIFY_POLICY_FILE ; 
 int /*<<< orphan*/  PAM_CHANGE_EXPIRED_AUTHTOK ; 
 int /*<<< orphan*/  PAM_DELETE_CRED ; 
 int /*<<< orphan*/  PAM_ESTABLISH_CRED ; 
 int /*<<< orphan*/  PAM_HOST ; 
 int /*<<< orphan*/  PAM_RHOST ; 
 int /*<<< orphan*/  PAM_RUSER ; 
 int /*<<< orphan*/  PAM_SILENT ; 
 int PAM_SUCCESS ; 
 int PAM_SYSTEM_ERR ; 
 int /*<<< orphan*/  PAM_TTY ; 
 int /*<<< orphan*/  STDERR_FILENO ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int gethostname (char*,int) ; 
 char* getlogin () ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  openpam_debug ; 
 int /*<<< orphan*/  openpam_set_feature (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int openpam_ttyconv_timeout ; 
 int /*<<< orphan*/  opt_num_once (int,long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opt_str_once (int,char const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ optind ; 
 int pt_acct_mgmt (int /*<<< orphan*/ ) ; 
 int pt_authenticate (int /*<<< orphan*/ ) ; 
 int pt_chauthtok (int /*<<< orphan*/ ) ; 
 int pt_close_session (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pt_end (int) ; 
 int pt_listenv () ; 
 int pt_open_session (int /*<<< orphan*/ ) ; 
 int pt_set_item (int /*<<< orphan*/ ,char const*) ; 
 int pt_setcred (int /*<<< orphan*/ ) ; 
 int pt_start (char const*,char const*) ; 
 int /*<<< orphan*/  silent ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* ttyname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  verbose ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

int
main(int argc, char *argv[])
{
	char hostname[1024];
	const char *rhost = NULL;
	const char *host = NULL;
	const char *ruser = NULL;
	const char *user = NULL;
	const char *service = NULL;
	const char *tty = NULL;
	long timeout = 0;
	int keepatit = 0;
	int pame;
	int opt;

	while ((opt = getopt(argc, argv, "dH:h:kMPsT:t:U:u:v")) != -1)
		switch (opt) {
		case 'd':
			openpam_debug++;
			break;
		case 'H':
			opt_str_once(opt, &rhost, optarg);
			break;
		case 'h':
			opt_str_once(opt, &host, optarg);
			break;
		case 'k':
			keepatit = 1;
			break;
		case 'M':
			openpam_set_feature(OPENPAM_RESTRICT_MODULE_NAME, 0);
			openpam_set_feature(OPENPAM_VERIFY_MODULE_FILE, 0);
			break;
		case 'P':
			openpam_set_feature(OPENPAM_RESTRICT_SERVICE_NAME, 0);
			openpam_set_feature(OPENPAM_VERIFY_POLICY_FILE, 0);
			break;
		case 's':
			silent = PAM_SILENT;
			break;
		case 'T':
			opt_num_once(opt, &timeout, optarg);
			if (timeout < 0 || timeout > INT_MAX) {
				fprintf(stderr,
				    "Invalid conversation timeout\n");
				usage();
			}
			openpam_ttyconv_timeout = (int)timeout;
			break;
		case 't':
			opt_str_once(opt, &tty, optarg);
			break;
		case 'U':
			opt_str_once(opt, &ruser, optarg);
			break;
		case 'u':
			opt_str_once(opt, &user, optarg);
			break;
		case 'v':
			verbose++;
			break;
		default:
			usage();
		}

	argc -= optind;
	argv += optind;

	if (argc < 1)
		usage();

	service = *argv;
	--argc;
	++argv;

	/* defaults */
	if (service == NULL)
		service = "pamtest";
	if (rhost == NULL) {
		if (gethostname(hostname, sizeof(hostname)) == -1)
			err(1, "gethostname()");
		rhost = hostname;
	}
	if (tty == NULL)
		tty = ttyname(STDERR_FILENO);
	if (user == NULL)
		user = getlogin();
	if (ruser == NULL)
		ruser = user;

	/* initialize PAM */
	if ((pame = pt_start(service, user)) != PAM_SUCCESS)
		goto end;

	/*
	 * pam_start(3) sets this to the machine's hostname, but we allow
	 * the user to override it.
	 */
	if (host != NULL)
		if ((pame = pt_set_item(PAM_HOST, host)) != PAM_SUCCESS)
		    goto end;

	/*
	 * The remote host / user / tty are usually set by the
	 * application.
	 */
	if ((pame = pt_set_item(PAM_RHOST, rhost)) != PAM_SUCCESS ||
	    (pame = pt_set_item(PAM_RUSER, ruser)) != PAM_SUCCESS ||
	    (pame = pt_set_item(PAM_TTY, tty)) != PAM_SUCCESS)
		goto end;

	while (argc > 0) {
		if (strcmp(*argv, "listenv") == 0 ||
		    strcmp(*argv, "env") == 0) {
			pame = pt_listenv();
		} else if (strcmp(*argv, "authenticate") == 0 ||
		    strcmp(*argv, "auth") == 0) {
			pame = pt_authenticate(0);
		} else if (strcmp(*argv, "acct_mgmt") == 0 ||
		    strcmp(*argv, "account") == 0) {
			pame = pt_acct_mgmt(0);
		} else if (strcmp(*argv, "chauthtok") == 0 ||
		    strcmp(*argv, "change") == 0) {
			pame = pt_chauthtok(PAM_CHANGE_EXPIRED_AUTHTOK);
		} else if (strcmp(*argv, "forcechauthtok") == 0 ||
		    strcmp(*argv, "forcechange") == 0) {
			pame = pt_chauthtok(0);
		} else if (strcmp(*argv, "setcred") == 0 ||
		    strcmp(*argv, "establish_cred") == 0) {
			pame = pt_setcred(PAM_ESTABLISH_CRED);
		} else if (strcmp(*argv, "open_session") == 0 ||
		    strcmp(*argv, "open") == 0) {
			pame = pt_open_session(0);
		} else if (strcmp(*argv, "close_session") == 0 ||
		    strcmp(*argv, "close") == 0) {
			pame = pt_close_session(0);
		} else if (strcmp(*argv, "unsetcred") == 0 ||
		    strcmp(*argv, "delete_cred") == 0) {
			pame = pt_setcred(PAM_DELETE_CRED);
		} else {
			warnx("unknown primitive: %s", *argv);
			pame = PAM_SYSTEM_ERR;
		}
		if (pame != PAM_SUCCESS && !keepatit) {
			warnx("test aborted");
			break;
		}
		--argc;
		++argv;
	}

end:
	(void)pt_end(pame);
	exit(pame == PAM_SUCCESS ? 0 : 1);
}