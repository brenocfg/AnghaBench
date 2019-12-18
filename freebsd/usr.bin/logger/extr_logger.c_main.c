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
typedef  int /*<<< orphan*/  time_t ;
struct socks {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int LOG_NOTICE ; 
 int LOG_PERROR ; 
 int LOG_PID ; 
 int LOG_USER ; 
 int MAXHOSTNAMELEN ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  PF_INET6 ; 
 int /*<<< orphan*/  _IONBF ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  ctime_r (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  err (int,char*,void*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  family ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * freopen (void*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gethostname (char*,int) ; 
 char* getlogin () ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  logmessage (int,char*,char*,char*,struct socks*,scalar_t__,char*) ; 
 int /*<<< orphan*/  openlog (char*,int,int /*<<< orphan*/ ) ; 
 void* optarg ; 
 scalar_t__ optind ; 
 int pencode (void*) ; 
 int /*<<< orphan*/  send_to_all ; 
 int /*<<< orphan*/  setvbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ socksetup (char const*,char*,char const*,struct socks**) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 char* strchrnul (char*,char) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unsetenv (char*) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	struct socks *socks;
	ssize_t nsock;
	time_t now;
	int ch, logflags, pri;
	char *tag, *host, buf[1024], *timestamp, tbuf[26],
	    *hostname, hbuf[MAXHOSTNAMELEN];
	const char *svcname, *src;

	tag = NULL;
	host = NULL;
	hostname = NULL;
	svcname = "syslog";
	src = NULL;
	socks = NULL;
	pri = LOG_USER | LOG_NOTICE;
	logflags = 0;
	unsetenv("TZ");
	while ((ch = getopt(argc, argv, "46Af:H:h:iP:p:S:st:")) != -1)
		switch((char)ch) {
		case '4':
			family = PF_INET;
			break;
#ifdef INET6
		case '6':
			family = PF_INET6;
			break;
#endif
		case 'A':
			send_to_all++;
			break;
		case 'f':		/* file to log */
			if (freopen(optarg, "r", stdin) == NULL)
				err(1, "%s", optarg);
			setvbuf(stdin, 0, _IONBF, 0);
			break;
		case 'H':		/* hostname to set in message header */
			hostname = optarg;
			break;
		case 'h':		/* hostname to deliver to */
			host = optarg;
			break;
		case 'i':		/* log process id also */
			logflags |= LOG_PID;
			break;
		case 'P':		/* service name or port number */
			svcname = optarg;
			break;
		case 'p':		/* priority */
			pri = pencode(optarg);
			break;
		case 's':		/* log to standard error */
			logflags |= LOG_PERROR;
			break;
		case 'S':		/* source address */
			src = optarg;
			break;
		case 't':		/* tag */
			tag = optarg;
			break;
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (host) {
		nsock = socksetup(src, host, svcname, &socks);
		if (nsock <= 0)
			errx(1, "socket");
	} else {
		if (src)
			errx(1, "-h option is missing.");
		nsock = 0;
	}

	if (tag == NULL)
		tag = getlogin();
	/* setup for logging */
	if (host == NULL)
		openlog(tag, logflags, 0);
	(void) fclose(stdout);

	(void )time(&now);
	(void )ctime_r(&now, tbuf);
	tbuf[19] = '\0';
	timestamp = tbuf + 4;

	if (hostname == NULL) {
		hostname = hbuf;
		(void )gethostname(hbuf, MAXHOSTNAMELEN);
		*strchrnul(hostname, '.') = '\0';
	}

	/* log input line if appropriate */
	if (argc > 0) {
		char *p, *endp;
		size_t len;

		for (p = buf, endp = buf + sizeof(buf) - 2; *argv;) {
			len = strlen(*argv);
			if (p + len > endp && p > buf) {
				logmessage(pri, timestamp, hostname, tag,
				    socks, nsock, buf);
				p = buf;
			}
			if (len > sizeof(buf) - 1)
				logmessage(pri, timestamp, hostname, tag,
				    socks, nsock, *argv++);
			else {
				if (p != buf)
					*p++ = ' ';
				bcopy(*argv++, p, len);
				*(p += len) = '\0';
			}
		}
		if (p != buf)
			logmessage(pri, timestamp, hostname, tag, socks, nsock,
			    buf);
	} else
		while (fgets(buf, sizeof(buf), stdin) != NULL)
			logmessage(pri, timestamp, hostname, tag, socks, nsock,
			    buf);
	exit(0);
}