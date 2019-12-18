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
typedef  int /*<<< orphan*/  wd ;
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_3__ {void* out_time; } ;
struct whoent {TYPE_1__ we_utmp; void* we_idle; } ;
struct whod {scalar_t__ wd_vers; scalar_t__ wd_type; char* wd_hostname; int /*<<< orphan*/  wd_recvtime; struct whoent* wd_we; void* wd_boottime; void** wd_loadav; void* wd_sendtime; } ;
struct stat {int st_size; } ;
struct sockaddr_in {scalar_t__ sin_port; int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  from ;
typedef  int /*<<< orphan*/  cap_rights_t ;
struct TYPE_4__ {scalar_t__ s_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_CREATE ; 
 int /*<<< orphan*/  CAP_FSTAT ; 
 int /*<<< orphan*/  CAP_FTRUNCATE ; 
 int /*<<< orphan*/  CAP_LOOKUP ; 
 int /*<<< orphan*/  CAP_SEEK ; 
 int /*<<< orphan*/  CAP_WRITE ; 
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int O_CREAT ; 
 int O_DIRECTORY ; 
 int O_RDONLY ; 
 int O_WRONLY ; 
 int WHDRSIZE ; 
 scalar_t__ WHODTYPE_STATUS ; 
 scalar_t__ WHODVERSION ; 
 int /*<<< orphan*/  _PATH_RWHODIR ; 
 int /*<<< orphan*/  _time_to_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cap_rights_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 scalar_t__ caph_enter () ; 
 scalar_t__ caph_rights_limit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 int /*<<< orphan*/  ftruncate (int,int) ; 
 int /*<<< orphan*/  inet_ntoa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  insecure_mode ; 
 void* ntohl (void*) ; 
 int /*<<< orphan*/  ntohs (scalar_t__) ; 
 int open (char*,int) ; 
 int openat (int,char*,int,int) ; 
 int recvfrom (int /*<<< orphan*/ ,struct whod*,int,int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  s ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 TYPE_2__* sp ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verify (char*,int) ; 
 int /*<<< orphan*/  write (int,char*,int) ; 

void
receiver_process(void)
{
	struct sockaddr_in from;
	struct stat st;
	cap_rights_t rights;
	char path[64];
	int dirfd;
	struct whod wd;
	socklen_t len;
	int cc, whod;
	time_t t;

	len = sizeof(from);
	dirfd = open(".", O_RDONLY | O_DIRECTORY);
	if (dirfd < 0) {
		syslog(LOG_WARNING, "%s: %m", _PATH_RWHODIR);
		exit(1);
	}
	cap_rights_init(&rights, CAP_CREATE, CAP_FSTAT, CAP_FTRUNCATE,
	    CAP_LOOKUP, CAP_SEEK, CAP_WRITE);
	if (caph_rights_limit(dirfd, &rights) < 0) {
		syslog(LOG_WARNING, "cap_rights_limit: %m");
		exit(1);
	}
	if (caph_enter() < 0) {
		syslog(LOG_ERR, "cap_enter: %m");
		exit(1);
	}
	for (;;) {
		cc = recvfrom(s, &wd, sizeof(wd), 0, (struct sockaddr *)&from,
		    &len);
		if (cc <= 0) {
			if (cc < 0 && errno != EINTR)
				syslog(LOG_WARNING, "recv: %m");
			continue;
		}
		if (from.sin_port != sp->s_port && !insecure_mode) {
			syslog(LOG_WARNING, "%d: bad source port from %s",
			    ntohs(from.sin_port), inet_ntoa(from.sin_addr));
			continue;
		}
		if (cc < WHDRSIZE) {
			syslog(LOG_WARNING, "short packet from %s",
			    inet_ntoa(from.sin_addr));
			continue;
		}
		if (wd.wd_vers != WHODVERSION)
			continue;
		if (wd.wd_type != WHODTYPE_STATUS)
			continue;
		if (!verify(wd.wd_hostname, sizeof(wd.wd_hostname))) {
			syslog(LOG_WARNING, "malformed host name from %s",
			    inet_ntoa(from.sin_addr));
			continue;
		}
		(void) snprintf(path, sizeof(path), "whod.%s", wd.wd_hostname);
		/*
		 * Rather than truncating and growing the file each time,
		 * use ftruncate if size is less than previous size.
		 */
		whod = openat(dirfd, path, O_WRONLY | O_CREAT, 0644);
		if (whod < 0) {
			syslog(LOG_WARNING, "%s: %m", path);
			continue;
		}
		cap_rights_init(&rights, CAP_FSTAT, CAP_FTRUNCATE, CAP_WRITE);
		if (caph_rights_limit(whod, &rights) < 0) {
			syslog(LOG_WARNING, "cap_rights_limit: %m");
			exit(1);
		}
#if ENDIAN != BIG_ENDIAN
		{
			struct whoent *we;
			int i, n;

			n = (cc - WHDRSIZE) / sizeof(struct whoent);
			/* undo header byte swapping before writing to file */
			wd.wd_sendtime = ntohl(wd.wd_sendtime);
			for (i = 0; i < 3; i++)
				wd.wd_loadav[i] = ntohl(wd.wd_loadav[i]);
			wd.wd_boottime = ntohl(wd.wd_boottime);
			we = wd.wd_we;
			for (i = 0; i < n; i++) {
				we->we_idle = ntohl(we->we_idle);
				we->we_utmp.out_time =
				    ntohl(we->we_utmp.out_time);
				we++;
			}
		}
#endif
		(void) time(&t);
		wd.wd_recvtime = _time_to_int(t);
		(void) write(whod, (char *)&wd, cc);
		if (fstat(whod, &st) < 0 || st.st_size > cc)
			ftruncate(whod, cc);
		(void) close(whod);
	}
	(void) close(dirfd);
}