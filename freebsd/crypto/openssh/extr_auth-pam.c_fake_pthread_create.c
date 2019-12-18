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
struct pam_ctxt {int pam_psock; int pam_csock; } ;
typedef  int /*<<< orphan*/  sp_pthread_t ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fork () ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sshpam_oldsig ; 
 int /*<<< orphan*/  sshpam_sigchld_handler ; 
 int sshpam_thread_status ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pthread_create(sp_pthread_t *thread, const void *attr,
    void *(*thread_start)(void *), void *arg)
{
	pid_t pid;
	struct pam_ctxt *ctx = arg;

	sshpam_thread_status = -1;
	switch ((pid = fork())) {
	case -1:
		error("fork(): %s", strerror(errno));
		return (-1);
	case 0:
		close(ctx->pam_psock);
		ctx->pam_psock = -1;
		thread_start(arg);
		_exit(1);
	default:
		*thread = pid;
		close(ctx->pam_csock);
		ctx->pam_csock = -1;
		sshpam_oldsig = signal(SIGCHLD, sshpam_sigchld_handler);
		return (0);
	}
}