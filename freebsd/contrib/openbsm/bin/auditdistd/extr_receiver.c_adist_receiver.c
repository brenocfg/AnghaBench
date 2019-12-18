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
struct adist_host {int adh_worker_pid; int adh_trail_fd; int /*<<< orphan*/  adh_name; int /*<<< orphan*/  adh_role; int /*<<< orphan*/ * adh_remote; } ;
struct adist_config {int /*<<< orphan*/  adc_timeout; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADIST_USER ; 
 int /*<<< orphan*/  EX_CONFIG ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 int /*<<< orphan*/  PJDLOG_VERIFY (int) ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 struct adist_config* adcfg ; 
 struct adist_host* adhost ; 
 int /*<<< orphan*/  descriptors_cleanup (struct adist_host*) ; 
 int /*<<< orphan*/  disk_thread ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int fork () ; 
 int /*<<< orphan*/  init_environment () ; 
 int pjdlog_debug_get () ; 
 int /*<<< orphan*/  pjdlog_debug_set (int) ; 
 int /*<<< orphan*/  pjdlog_errno (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pjdlog_info (char*) ; 
 int /*<<< orphan*/  pjdlog_init (int) ; 
 int pjdlog_mode_get () ; 
 int /*<<< orphan*/  pjdlog_prefix_set (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proto_close (int /*<<< orphan*/ *) ; 
 int proto_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct adist_host*) ; 
 int /*<<< orphan*/  receiver_connect () ; 
 int /*<<< orphan*/  receiver_directory_open () ; 
 int /*<<< orphan*/  recv_thread ; 
 int /*<<< orphan*/  role2str (int /*<<< orphan*/ ) ; 
 scalar_t__ sandbox (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_thread (struct adist_host*) ; 
 int /*<<< orphan*/  setproctitle (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sigemptyset (int /*<<< orphan*/ *) ; 
 scalar_t__ sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
adist_receiver(struct adist_config *config, struct adist_host *adh)
{
	sigset_t mask;
	pthread_t td;
	pid_t pid;
	int error, mode, debuglevel;

	pid = fork();
	if (pid == -1) {
		pjdlog_errno(LOG_ERR, "Unable to fork");
		proto_close(adh->adh_remote);
		adh->adh_remote = NULL;
		return;
	}

	if (pid > 0) {
		/* This is parent. */
		proto_close(adh->adh_remote);
		adh->adh_remote = NULL;
		adh->adh_worker_pid = pid;
		return;
	}

	adcfg = config;
	adhost = adh;
	mode = pjdlog_mode_get();
	debuglevel = pjdlog_debug_get();

	descriptors_cleanup(adhost);

//	descriptors_assert(adhost, mode);

	pjdlog_init(mode);
	pjdlog_debug_set(debuglevel);
	pjdlog_prefix_set("[%s] (%s) ", adhost->adh_name,
	    role2str(adhost->adh_role));
#ifdef HAVE_SETPROCTITLE
	setproctitle("%s (%s)", adhost->adh_name, role2str(adhost->adh_role));
#endif

	PJDLOG_VERIFY(sigemptyset(&mask) == 0);
	PJDLOG_VERIFY(sigprocmask(SIG_SETMASK, &mask, NULL) == 0);

	/* Error in setting timeout is not critical, but why should it fail? */
	if (proto_timeout(adhost->adh_remote, adcfg->adc_timeout) == -1)
		pjdlog_errno(LOG_WARNING, "Unable to set connection timeout");

	init_environment();

	adhost->adh_trail_fd = -1;
	receiver_directory_open();

	if (sandbox(ADIST_USER, true, "auditdistd: %s (%s)",
	    role2str(adhost->adh_role), adhost->adh_name) != 0) {
		exit(EX_CONFIG);
	}
	pjdlog_info("Privileges successfully dropped.");

	receiver_connect();

	error = pthread_create(&td, NULL, recv_thread, adhost);
	PJDLOG_ASSERT(error == 0);
	error = pthread_create(&td, NULL, disk_thread, adhost);
	PJDLOG_ASSERT(error == 0);
	(void)send_thread(adhost);
}