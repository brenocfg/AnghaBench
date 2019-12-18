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
typedef  int /*<<< orphan*/  uid_t ;
typedef  int /*<<< orphan*/  token_t ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  gid_t ;
struct TYPE_2__ {int /*<<< orphan*/  pw_gid; int /*<<< orphan*/  pw_uid; } ;

/* Variables and functions */
 int AUC_NOAUDIT ; 
 int /*<<< orphan*/  AUE_logout ; 
 int /*<<< orphan*/  A_GETCOND ; 
 scalar_t__ ENOSYS ; 
 int au_close (int,int,int /*<<< orphan*/ ) ; 
 int au_open () ; 
 int /*<<< orphan*/ * au_to_return32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * au_to_subject32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  au_write (int,int /*<<< orphan*/ *) ; 
 scalar_t__ auditon (int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  getegid () ; 
 int /*<<< orphan*/  geteuid () ; 
 int /*<<< orphan*/  getpid () ; 
 TYPE_1__* pwd ; 
 int /*<<< orphan*/  tid ; 

void
audit_logout(void)
{
	token_t *tok;
	int aufd;
	uid_t uid = pwd->pw_uid;
	gid_t gid = pwd->pw_gid;
	pid_t pid = getpid();
	int au_cond;

	/* If we are not auditing, don't cut an audit record; just return. */
 	if (auditon(A_GETCOND, &au_cond, sizeof(int)) < 0) {
		if (errno == ENOSYS)
			return;
		errx(1, "could not determine audit condition");
	}
	if (au_cond == AUC_NOAUDIT)
		return;

	if ((aufd = au_open()) == -1)
		errx(1, "audit error: au_open() failed");

	/* The subject that is created (euid, egid of the current process). */
	if ((tok = au_to_subject32(uid, geteuid(), getegid(), uid, gid, pid,
	    pid, &tid)) == NULL)
		errx(1, "audit error: au_to_subject32() failed");
	au_write(aufd, tok);

	if ((tok = au_to_return32(0, 0)) == NULL)
		errx(1, "audit error: au_to_return32() failed");
	au_write(aufd, tok);

	if (au_close(aufd, 1, AUE_logout) == -1)
		errx(1, "audit record was not committed.");
}