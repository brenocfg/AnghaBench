#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; int /*<<< orphan*/  sin_port; } ;
struct sockaddr {int dummy; } ;
struct pcap_pkthdr {void* len; void* caplen; int /*<<< orphan*/  ts; } ;
typedef  void* ssize_t ;
typedef  int /*<<< orphan*/  sin ;
typedef  int /*<<< orphan*/  pcap_t ;
typedef  int /*<<< orphan*/  pcap_dumper_t ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int BUFMAX ; 
 int /*<<< orphan*/  DLT_RAW ; 
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  IPPROTO_DIVERT ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SOCK_RAW ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  atol (char*) ; 
 int bind (int,struct sockaddr*,int) ; 
 scalar_t__ debug ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  gettimeofday (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htons (int) ; 
 scalar_t__ maxbytes ; 
 scalar_t__ maxpkts ; 
 int /*<<< orphan*/  okay (int) ; 
 char* optarg ; 
 int optind ; 
 int /*<<< orphan*/  pcap_dump (int /*<<< orphan*/ *,struct pcap_pkthdr*,char*) ; 
 int /*<<< orphan*/ * pcap_dump_open (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * pcap_open_dead (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcap_perror (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  pidfile ; 
 char* prog ; 
 int /*<<< orphan*/  quit (int) ; 
 void* recvfrom (int,char*,int,int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int reflect ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sendto (int,char*,void*,int /*<<< orphan*/ ,struct sockaddr*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ totbytes ; 
 scalar_t__ totpkts ; 
 int /*<<< orphan*/  usage () ; 

int
main(int ac, char *av[])
{
	int r, sd, portnum, l;
        struct sockaddr_in sin;
	int errflg = 0;

	int nfd;
	fd_set rds;

	ssize_t nr;

	char *dumpf, buf[BUFMAX];

	pcap_t *p;
	pcap_dumper_t *dp;
	struct pcap_pkthdr phd;

	prog = av[0];

	while ((r = getopt(ac, av, "drb:p:P:")) != -1) {
		switch (r) {
		case 'd':
			debug++;
			break;
		case 'r':
			reflect++;
			break;
		case 'b':
			maxbytes = (ssize_t) atol(optarg);
			break;
		case 'p':
			maxpkts = (ssize_t) atoi(optarg);
			break;
		case 'P':
			strcpy(pidfile, optarg);
			break;
		case '?':
		default:
			errflg++;
			break;
		}
	}

	if ((ac - optind) != 2 || errflg)
		usage();

	portnum = atoi(av[optind++]);
	dumpf = av[optind];

if (debug) fprintf(stderr, "bind to %d.\ndump to '%s'.\n", portnum, dumpf);

	if ((r = socket(PF_INET, SOCK_RAW, IPPROTO_DIVERT)) == -1) {
		perror("socket(DIVERT)");
		exit(2);
	}
	sd = r;

	sin.sin_port = htons(portnum);
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;

	if (bind(sd, (struct sockaddr *)&sin, sizeof(sin)) == -1) {
		perror("bind(divert)");
		exit(3);
	}

	p = pcap_open_dead(DLT_RAW, BUFMAX);
	dp = pcap_dump_open(p, dumpf);
	if (dp == NULL) {
		pcap_perror(p, dumpf);
		exit(4);
	}

	okay(portnum);

	nfd = sd + 1;
	for (;;) {
		FD_ZERO(&rds);
		FD_SET(sd, &rds);

		r = select(nfd, &rds, NULL, NULL, NULL);
		if (r == -1) {
			if (errno == EINTR) continue;
			perror("select");
			quit(11);
		}

		if (!FD_ISSET(sd, &rds))
			/* hmm. no work. */
			continue;

		/*
		 * use recvfrom(3 and sendto(3) as in natd(8).
		 * see /usr/src/sbin/natd/natd.c
		 * see ipfw(8) about using 'divert' and 'tee'.
		 */

		/*
		 * read packet.
		 */
		l = sizeof(sin);
		nr = recvfrom(sd, buf, sizeof(buf), 0, (struct sockaddr *)&sin, &l);
if (debug) fprintf(stderr, "recvfrom(%d) = %zd (%d)\n", sd, nr, l);
		if (nr < 0 && errno != EINTR) {
			perror("recvfrom(sd)");
			quit(12);
		}
		if (nr <= 0) continue;

		if (reflect) {
			/*
			 * write packet back so it can continue
			 * being processed by any further IPFW rules.
			 */
			l = sizeof(sin);
			r = sendto(sd, buf, nr, 0, (struct sockaddr *)&sin, l);
if (debug) fprintf(stderr, "  sendto(%d) = %d\n", sd, r);
			if (r < 0) { perror("sendto(sd)"); quit(13); }
		}

		/*
		 * check maximums, if any.
		 * but don't quit if must continue reflecting packets.
		 */
		if (maxpkts) {
			totpkts++;
			if (totpkts > maxpkts) {
				if (reflect == 1) continue;
				quit(0);
			}
		}
		if (maxbytes) {
			totbytes += nr;
			if (totbytes > maxbytes) {
				if (reflect == 1) continue;
				quit(0);
			}
		}

		/*
		 * save packet in tcpdump(1) format. see pcap(3).
		 * divert packets are fully assembled. see ipfw(8).
		 */
		(void) gettimeofday(&(phd.ts), NULL);
		phd.caplen = phd.len = nr;
		pcap_dump((u_char *)dp, &phd, buf);
		if (ferror((FILE *)dp)) { perror(dumpf); quit(14); }
		(void) fflush((FILE *)dp);
	}

	quit(0);
}