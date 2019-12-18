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
struct kinfo_proc {scalar_t__ ki_stat; int /*<<< orphan*/  ki_wmesg; } ;
typedef  int /*<<< orphan*/  semid_t ;
typedef  int pid_t ;
typedef  int /*<<< orphan*/  kvm_t ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  KERN_PROC_PID ; 
 int /*<<< orphan*/  O_RDONLY ; 
 scalar_t__ SSLEEP ; 
 int _POSIX2_LINE_MAX ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fail_err (char*,char*) ; 
 int /*<<< orphan*/  fail_errno (char*) ; 
 int fork () ; 
 int /*<<< orphan*/  ksem_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ksem_destroy_should_fail (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ksem_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ksem_post (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ksem_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_close (int /*<<< orphan*/ *) ; 
 char* kvm_geterr (int /*<<< orphan*/ *) ; 
 struct kinfo_proc* kvm_getprocs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/ * kvm_openfiles (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  usleep (int) ; 
 int /*<<< orphan*/  waitpid (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
busy_destroy_test(void)
{
	char errbuf[_POSIX2_LINE_MAX];
	struct kinfo_proc *kp;
	semid_t id;
	pid_t pid;
	kvm_t *kd;
	int count;

	kd = kvm_openfiles(NULL, "/dev/null", NULL, O_RDONLY, errbuf);
	if (kd == NULL) {
		fail_err("kvm_openfiles: %s", errbuf);
		return;
	}

	if (ksem_init(&id, 0) < 0) {
		fail_errno("ksem_init");
		kvm_close(kd);
		return;
	}

	pid = fork();
	switch (pid) {
	case -1:
		/* Error. */
		fail_errno("fork");
		ksem_destroy(id);
		kvm_close(kd);
		return;
	case 0:
		/* Child. */
		ksem_wait(id);
		exit(0);
	}

	/*
	 * Wait for the child process to block on the semaphore.  This
	 * is a bit gross.
	 */
	for (;;) {
		kp = kvm_getprocs(kd, KERN_PROC_PID, pid, &count);
		if (kp == NULL) {
			fail_err("kvm_getprocs: %s", kvm_geterr(kd));
			kvm_close(kd);
			ksem_destroy(id);
			return;
		}
		if (kp->ki_stat == SSLEEP &&
		    (strcmp(kp->ki_wmesg, "sem") == 0 ||
		    strcmp(kp->ki_wmesg, "ksem") == 0))
			break;
		usleep(1000);
	}
	kvm_close(kd);

	ksem_destroy_should_fail(id, EBUSY);

	/* Cleanup. */
	ksem_post(id);
	waitpid(pid, NULL, 0);
	ksem_destroy(id);
}