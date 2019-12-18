#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int logtype; scalar_t__ size; int /*<<< orphan*/  fd; scalar_t__ regular; } ;
typedef  TYPE_1__ logsource_t ;
typedef  int /*<<< orphan*/  iplog_t ;
typedef  int /*<<< orphan*/  fd_set ;
struct TYPE_7__ {int /*<<< orphan*/ * log; int /*<<< orphan*/ * cfile; int /*<<< orphan*/ * bfile; int /*<<< orphan*/ * blog; int /*<<< orphan*/ * file; TYPE_1__* logsrc; scalar_t__ maxfd; int /*<<< orphan*/  fdmr; } ;
typedef  TYPE_2__ config_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int DEFAULT_IPFLOGSIZE ; 
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  FD_ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int IPMON_SYSLOG ; 
 int IPMON_TAIL ; 
 int /*<<< orphan*/  LOG_CRIT ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 scalar_t__ donehup ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 void* fopen (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  init_tabs () ; 
 int /*<<< orphan*/  ipferror (int /*<<< orphan*/ ,char*) ; 
 int ipmonopts ; 
 int /*<<< orphan*/  load_config (int /*<<< orphan*/ *) ; 
 scalar_t__ lseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_log (TYPE_2__*,TYPE_1__*,char*,int) ; 
 int read_log (int /*<<< orphan*/ ,int*,char*,int) ; 
 int select (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int read_loginfo(config_t *conf)
{
	iplog_t buf[DEFAULT_IPFLOGSIZE/sizeof(iplog_t)+1];
	int n, tr, nr, i;
	logsource_t *l;
	fd_set fdr;

	fdr = conf->fdmr;

	n = select(conf->maxfd + 1, &fdr, NULL, NULL, NULL);
	if (n == 0)
		return 1;
	if (n == -1) {
		if (errno == EINTR)
			return 1;
		return -1;
	}

	for (i = 0, nr = 0; i < 3; i++) {
		l = &conf->logsrc[i];

		if ((l->logtype == -1) || !FD_ISSET(l->fd, &fdr))
			continue;

		tr = 0;
		if (l->regular) {
			tr = (lseek(l->fd, 0, SEEK_CUR) < l->size);
			if (!tr && !(ipmonopts & IPMON_TAIL))
				return 0;
		}

		n = 0;
		tr = read_log(l->fd, &n, (char *)buf, sizeof(buf));
		if (donehup) {
			if (conf->file != NULL) {
				if (conf->log != NULL) {
					fclose(conf->log);
					conf->log = NULL;
				}
				conf->log = fopen(conf->file, "a");
			}

			if (conf->bfile != NULL) {
				if (conf->blog != NULL) {
					fclose(conf->blog);
					conf->blog = NULL;
				}
				conf->blog = fopen(conf->bfile, "a");
			}

			init_tabs();
			if (conf->cfile != NULL)
				load_config(conf->cfile);
			donehup = 0;
		}

		switch (tr)
		{
		case -1 :
			if (ipmonopts & IPMON_SYSLOG)
				syslog(LOG_CRIT, "read: %m\n");
			else {
				ipferror(l->fd, "read");
			}
			return 0;
		case 1 :
			if (ipmonopts & IPMON_SYSLOG)
				syslog(LOG_CRIT, "aborting logging\n");
			else if (conf->log != NULL)
				fprintf(conf->log, "aborting logging\n");
			return 0;
		case 2 :
			break;
		case 0 :
			nr += tr;
			if (n > 0) {
				print_log(conf, l, (char *)buf, n);
				if (!(ipmonopts & IPMON_SYSLOG))
					fflush(conf->log);
			}
			break;
		}
	}

	if (!nr && (ipmonopts & IPMON_TAIL))
		sleep(1);

	return 1;
}