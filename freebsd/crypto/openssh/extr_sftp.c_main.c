#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sftp_conn {int dummy; } ;
typedef  int /*<<< orphan*/  args ;
struct TYPE_6__ {int /*<<< orphan*/ * list; } ;
typedef  TYPE_1__ arglist ;
typedef  int /*<<< orphan*/  LogLevel ;

/* Variables and functions */
 size_t DEFAULT_COPY_BUFLEN ; 
 size_t DEFAULT_NUM_REQUESTS ; 
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  SHUT_RDWR ; 
 int /*<<< orphan*/  STDERR_FILENO ; 
 int /*<<< orphan*/  SYSLOG_FACILITY_USER ; 
 int /*<<< orphan*/  SYSLOG_LEVEL_DEBUG1 ; 
 int /*<<< orphan*/  SYSLOG_LEVEL_ERROR ; 
 int /*<<< orphan*/  SYSLOG_LEVEL_INFO ; 
 char* _PATH_SFTP_SERVER ; 
 char* _PATH_SSH_PROGRAM ; 
 int /*<<< orphan*/  __progname ; 
 int a2port (char*) ; 
 int /*<<< orphan*/  addargs (TYPE_1__*,char*,...) ; 
 int batchmode ; 
 char* cleanhostname (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  connect_to_server (char*,int /*<<< orphan*/ *,int*,int*) ; 
 struct sftp_conn* do_init (int,int,size_t,size_t,long long) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fatal (char*,...) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  freeargs (TYPE_1__*) ; 
 int getopt (int,char**,char*) ; 
 int global_aflag ; 
 int global_fflag ; 
 int global_pflag ; 
 int global_rflag ; 
 int /*<<< orphan*/ * infile ; 
 int interactive_loop (struct sftp_conn*,char*,char*) ; 
 int /*<<< orphan*/  isatty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_init (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,char,int) ; 
 int /*<<< orphan*/  msetlocale () ; 
 int parse_uri (char*,char*,char**,char**,int*,char**) ; 
 int parse_user_host_path (char*,char**,char**,char**) ; 
 int quiet ; 
 int /*<<< orphan*/  replacearg (TYPE_1__*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  sanitise_stdfd () ; 
 scalar_t__ showprogress ; 
 int /*<<< orphan*/  shutdown (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssh_get_progname (char*) ; 
 int /*<<< orphan*/  ssh_malloc_init () ; 
 int sshpid ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* strerror (scalar_t__) ; 
 size_t strtol (char*,char**,int) ; 
 long long strtonum (char*,int,int,char const**) ; 
 int /*<<< orphan*/  usage () ; 
 int waitpid (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* xstrdup (char*) ; 

int
main(int argc, char **argv)
{
	int in, out, ch, err, tmp, port = -1;
	char *host = NULL, *user, *cp, *file2 = NULL;
	int debug_level = 0, sshver = 2;
	char *file1 = NULL, *sftp_server = NULL;
	char *ssh_program = _PATH_SSH_PROGRAM, *sftp_direct = NULL;
	const char *errstr;
	LogLevel ll = SYSLOG_LEVEL_INFO;
	arglist args;
	extern int optind;
	extern char *optarg;
	struct sftp_conn *conn;
	size_t copy_buffer_len = DEFAULT_COPY_BUFLEN;
	size_t num_requests = DEFAULT_NUM_REQUESTS;
	long long limit_kbps = 0;

	ssh_malloc_init();	/* must be called before any mallocs */
	/* Ensure that fds 0, 1 and 2 are open or directed to /dev/null */
	sanitise_stdfd();
	msetlocale();

	__progname = ssh_get_progname(argv[0]);
	memset(&args, '\0', sizeof(args));
	args.list = NULL;
	addargs(&args, "%s", ssh_program);
	addargs(&args, "-oForwardX11 no");
	addargs(&args, "-oForwardAgent no");
	addargs(&args, "-oPermitLocalCommand no");
	addargs(&args, "-oClearAllForwardings yes");

	ll = SYSLOG_LEVEL_INFO;
	infile = stdin;

	while ((ch = getopt(argc, argv,
	    "1246afhpqrvCc:D:i:l:o:s:S:b:B:F:P:R:")) != -1) {
		switch (ch) {
		/* Passed through to ssh(1) */
		case '4':
		case '6':
		case 'C':
			addargs(&args, "-%c", ch);
			break;
		/* Passed through to ssh(1) with argument */
		case 'F':
		case 'c':
		case 'i':
		case 'o':
			addargs(&args, "-%c", ch);
			addargs(&args, "%s", optarg);
			break;
		case 'q':
			ll = SYSLOG_LEVEL_ERROR;
			quiet = 1;
			showprogress = 0;
			addargs(&args, "-%c", ch);
			break;
		case 'P':
			port = a2port(optarg);
			if (port <= 0)
				fatal("Bad port \"%s\"\n", optarg);
			break;
		case 'v':
			if (debug_level < 3) {
				addargs(&args, "-v");
				ll = SYSLOG_LEVEL_DEBUG1 + debug_level;
			}
			debug_level++;
			break;
		case '1':
			sshver = 1;
			if (sftp_server == NULL)
				sftp_server = _PATH_SFTP_SERVER;
			break;
		case '2':
			sshver = 2;
			break;
		case 'a':
			global_aflag = 1;
			break;
		case 'B':
			copy_buffer_len = strtol(optarg, &cp, 10);
			if (copy_buffer_len == 0 || *cp != '\0')
				fatal("Invalid buffer size \"%s\"", optarg);
			break;
		case 'b':
			if (batchmode)
				fatal("Batch file already specified.");

			/* Allow "-" as stdin */
			if (strcmp(optarg, "-") != 0 &&
			    (infile = fopen(optarg, "r")) == NULL)
				fatal("%s (%s).", strerror(errno), optarg);
			showprogress = 0;
			quiet = batchmode = 1;
			addargs(&args, "-obatchmode yes");
			break;
		case 'f':
			global_fflag = 1;
			break;
		case 'p':
			global_pflag = 1;
			break;
		case 'D':
			sftp_direct = optarg;
			break;
		case 'l':
			limit_kbps = strtonum(optarg, 1, 100 * 1024 * 1024,
			    &errstr);
			if (errstr != NULL)
				usage();
			limit_kbps *= 1024; /* kbps */
			break;
		case 'r':
			global_rflag = 1;
			break;
		case 'R':
			num_requests = strtol(optarg, &cp, 10);
			if (num_requests == 0 || *cp != '\0')
				fatal("Invalid number of requests \"%s\"",
				    optarg);
			break;
		case 's':
			sftp_server = optarg;
			break;
		case 'S':
			ssh_program = optarg;
			replacearg(&args, 0, "%s", ssh_program);
			break;
		case 'h':
		default:
			usage();
		}
	}

	if (!isatty(STDERR_FILENO))
		showprogress = 0;

	log_init(argv[0], ll, SYSLOG_FACILITY_USER, 1);

	if (sftp_direct == NULL) {
		if (optind == argc || argc > (optind + 2))
			usage();
		argv += optind;

		switch (parse_uri("sftp", *argv, &user, &host, &tmp, &file1)) {
		case -1:
			usage();
			break;
		case 0:
			if (tmp != -1)
				port = tmp;
			break;
		default:
			if (parse_user_host_path(*argv, &user, &host,
			    &file1) == -1) {
				/* Treat as a plain hostname. */
				host = xstrdup(*argv);
				host = cleanhostname(host);
			}
			break;
		}
		file2 = *(argv + 1);

		if (!*host) {
			fprintf(stderr, "Missing hostname\n");
			usage();
		}

		if (port != -1)
			addargs(&args, "-oPort %d", port);
		if (user != NULL) {
			addargs(&args, "-l");
			addargs(&args, "%s", user);
		}
		addargs(&args, "-oProtocol %d", sshver);

		/* no subsystem if the server-spec contains a '/' */
		if (sftp_server == NULL || strchr(sftp_server, '/') == NULL)
			addargs(&args, "-s");

		addargs(&args, "--");
		addargs(&args, "%s", host);
		addargs(&args, "%s", (sftp_server != NULL ?
		    sftp_server : "sftp"));

		connect_to_server(ssh_program, args.list, &in, &out);
	} else {
		args.list = NULL;
		addargs(&args, "sftp-server");

		connect_to_server(sftp_direct, args.list, &in, &out);
	}
	freeargs(&args);

	conn = do_init(in, out, copy_buffer_len, num_requests, limit_kbps);
	if (conn == NULL)
		fatal("Couldn't initialise connection to server");

	if (!quiet) {
		if (sftp_direct == NULL)
			fprintf(stderr, "Connected to %s.\n", host);
		else
			fprintf(stderr, "Attached to %s.\n", sftp_direct);
	}

	err = interactive_loop(conn, file1, file2);

#if !defined(USE_PIPES)
	shutdown(in, SHUT_RDWR);
	shutdown(out, SHUT_RDWR);
#endif

	close(in);
	close(out);
	if (batchmode)
		fclose(infile);

	while (waitpid(sshpid, NULL, 0) == -1 && sshpid > 1)
		if (errno != EINTR)
			fatal("Couldn't wait for ssh process: %s",
			    strerror(errno));

	exit(err == 0 ? 0 : 1);
}