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
typedef  int uid_t ;
typedef  int /*<<< orphan*/  token_t ;
typedef  int pid_t ;
typedef  int gid_t ;
typedef  int /*<<< orphan*/  au_cond ;
struct TYPE_2__ {int pw_uid; int pw_gid; } ;

/* Variables and functions */
 int AUC_NOAUDIT ; 
 int /*<<< orphan*/  AUE_login ; 
 int /*<<< orphan*/  A_GETCOND ; 
 scalar_t__ ENOSYS ; 
 int au_close (int,int,int /*<<< orphan*/ ) ; 
 int au_open () ; 
 int /*<<< orphan*/ * au_to_return32 (int,scalar_t__) ; 
 int /*<<< orphan*/ * au_to_subject32 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * au_to_text (char const*) ; 
 int /*<<< orphan*/  au_write (int,int /*<<< orphan*/ *) ; 
 scalar_t__ auditon (int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  getegid () ; 
 int /*<<< orphan*/  geteuid () ; 
 int getpid () ; 
 TYPE_1__* pwd ; 
 int /*<<< orphan*/  tid ; 

void
au_login_fail(const char *errmsg, int na)
{
	token_t *tok;
	int aufd;
	int au_cond;
	uid_t uid;
	gid_t gid;
	pid_t pid = getpid();

	/* If we are not auditing, don't cut an audit record; just return. */
 	if (auditon(A_GETCOND, &au_cond, sizeof(au_cond)) < 0) {
		if (errno == ENOSYS)
			return;
		errx(1, "could not determine audit condition");
	}
	if (au_cond == AUC_NOAUDIT)
		return;

	if ((aufd = au_open()) == -1)
		errx(1, "audit error: au_open() failed");

	if (na) {
		/*
		 * Non attributable event.  Assuming that login is not called
		 * within a user's session => auid,asid == -1.
		 */
		if ((tok = au_to_subject32(-1, geteuid(), getegid(), -1, -1,
		    pid, -1, &tid)) == NULL)
			errx(1, "audit error: au_to_subject32() failed");
	} else {
		/* We know the subject -- so use its value instead. */
		uid = pwd->pw_uid;
		gid = pwd->pw_gid;
		if ((tok = au_to_subject32(uid, geteuid(), getegid(), uid,
		    gid, pid, pid, &tid)) == NULL)
			errx(1, "audit error: au_to_subject32() failed");
	}
	au_write(aufd, tok);

	/* Include the error message. */
	if ((tok = au_to_text(errmsg)) == NULL)
		errx(1, "audit error: au_to_text() failed");
	au_write(aufd, tok);

	if ((tok = au_to_return32(1, errno)) == NULL)
		errx(1, "audit error: au_to_return32() failed");
	au_write(aufd, tok);

	if (au_close(aufd, 1, AUE_login) == -1)
		errx(1, "audit error: au_close() was not committed");
}