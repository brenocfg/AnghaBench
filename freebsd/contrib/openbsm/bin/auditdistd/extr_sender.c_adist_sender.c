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
struct adist_host {int adh_worker_pid; int adh_reset; int /*<<< orphan*/  adh_remoteaddr; int /*<<< orphan*/  adh_name; int /*<<< orphan*/  adh_role; int /*<<< orphan*/  adh_directory; int /*<<< orphan*/ * adh_conn; } ;
struct adist_config {int dummy; } ;
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADIST_USER ; 
 int /*<<< orphan*/  EX_CONFIG ; 
 int /*<<< orphan*/  EX_OSFILE ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 struct adist_config* adcfg ; 
 struct adist_host* adhost ; 
 int /*<<< orphan*/ * adist_trail ; 
 int /*<<< orphan*/  descriptors_assert (struct adist_host*,int) ; 
 int /*<<< orphan*/  descriptors_cleanup (struct adist_host*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int fork () ; 
 int /*<<< orphan*/  guard_thread ; 
 int /*<<< orphan*/  init_environment () ; 
 int pjdlog_debug_get () ; 
 int /*<<< orphan*/  pjdlog_debug_set (int) ; 
 int /*<<< orphan*/  pjdlog_errno (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pjdlog_info (char*,...) ; 
 int /*<<< orphan*/  pjdlog_init (int) ; 
 int pjdlog_mode_get () ; 
 int /*<<< orphan*/  pjdlog_prefix_set (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proto_close (int /*<<< orphan*/ *) ; 
 int proto_connect (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  proto_recv (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proto_send (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_thread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  recv_thread ; 
 int /*<<< orphan*/  role2str (int /*<<< orphan*/ ) ; 
 scalar_t__ sandbox (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_thread ; 
 scalar_t__ sender_connect () ; 
 int /*<<< orphan*/  setproctitle (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trail_dirfd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * trail_new (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wait_for_dir_init (int /*<<< orphan*/ ) ; 

void
adist_sender(struct adist_config *config, struct adist_host *adh)
{
	pthread_t td;
	pid_t pid;
	int error, mode, debuglevel;

	/*
	 * Create communication channel for sending connection requests from
	 * child to parent.
	 */
	if (proto_connect(NULL, "socketpair://", -1, &adh->adh_conn) == -1) {
		pjdlog_errno(LOG_ERR,
		    "Unable to create connection sockets between child and parent");
		return;
	}

	pid = fork();
	if (pid == -1) {
		pjdlog_errno(LOG_ERR, "Unable to fork");
		proto_close(adh->adh_conn);
		adh->adh_conn = NULL;
		return;
	}

	if (pid > 0) {
		/* This is parent. */
		adh->adh_worker_pid = pid;
		/* Declare that we are receiver. */
		proto_recv(adh->adh_conn, NULL, 0);
		return;
	}

	adcfg = config;
	adhost = adh;

	mode = pjdlog_mode_get();
	debuglevel = pjdlog_debug_get();

	/* Declare that we are sender. */
	proto_send(adhost->adh_conn, NULL, 0);

	descriptors_cleanup(adhost);

#ifdef TODO
	descriptors_assert(adhost, mode);
#endif

	pjdlog_init(mode);
	pjdlog_debug_set(debuglevel);
	pjdlog_prefix_set("[%s] (%s) ", adhost->adh_name,
	    role2str(adhost->adh_role));
#ifdef HAVE_SETPROCTITLE
	setproctitle("[%s] (%s) ", adhost->adh_name,
	    role2str(adhost->adh_role));
#endif

	/*
	 * The sender process should be able to remove entries from its
	 * trail directory, but it should not be able to write to the
	 * trail files, only read from them.
	 */
	adist_trail = trail_new(adhost->adh_directory, false);
	if (adist_trail == NULL)
		exit(EX_OSFILE);

	if (sandbox(ADIST_USER, true, "auditdistd: %s (%s)",
	    role2str(adhost->adh_role), adhost->adh_name) != 0) {
		exit(EX_CONFIG);
	}
	pjdlog_info("Privileges successfully dropped.");

	/*
	 * We can ignore wait_for_dir_init() failures. It will fall back to
	 * using sleep(3).
	 */
	(void)wait_for_dir_init(trail_dirfd(adist_trail));

	init_environment();
	if (sender_connect() == 0) {
		pjdlog_info("Successfully connected to %s.",
		    adhost->adh_remoteaddr);
	}
	adhost->adh_reset = true;

	/*
	 * Create the guard thread first, so we can handle signals from the
	 * very begining.
	 */
	error = pthread_create(&td, NULL, guard_thread, NULL);
	PJDLOG_ASSERT(error == 0);
	error = pthread_create(&td, NULL, send_thread, NULL);
	PJDLOG_ASSERT(error == 0);
	error = pthread_create(&td, NULL, recv_thread, NULL);
	PJDLOG_ASSERT(error == 0);
	(void)read_thread(NULL);
}