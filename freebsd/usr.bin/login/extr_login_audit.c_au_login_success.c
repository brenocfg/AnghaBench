#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uid_t ;
typedef  int /*<<< orphan*/  token_t ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  gid_t ;
struct TYPE_4__ {int /*<<< orphan*/  ai_mask; int /*<<< orphan*/  ai_termid; int /*<<< orphan*/  ai_asid; int /*<<< orphan*/  ai_auid; } ;
typedef  TYPE_1__ auditinfo_t ;
typedef  int /*<<< orphan*/  au_mask_t ;
typedef  int /*<<< orphan*/  au_cond ;
struct TYPE_5__ {int /*<<< orphan*/  pw_name; int /*<<< orphan*/  pw_gid; int /*<<< orphan*/  pw_uid; } ;

/* Variables and functions */
 int AUC_NOAUDIT ; 
 int /*<<< orphan*/  AUE_login ; 
 int /*<<< orphan*/  A_GETCOND ; 
 scalar_t__ ENOSYS ; 
 int au_close (int,int,int /*<<< orphan*/ ) ; 
 int au_open () ; 
 int /*<<< orphan*/ * au_to_return32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * au_to_subject32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int au_user_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  au_write (int,int /*<<< orphan*/ *) ; 
 scalar_t__ auditon (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  getegid () ; 
 int /*<<< orphan*/  geteuid () ; 
 int /*<<< orphan*/  getpid () ; 
 TYPE_3__* pwd ; 
 scalar_t__ setaudit (TYPE_1__*) ; 
 int /*<<< orphan*/  tid ; 

void
au_login_success(void)
{
	token_t *tok;
	int aufd;
	au_mask_t aumask;
	auditinfo_t auinfo;
	uid_t uid = pwd->pw_uid;
	gid_t gid = pwd->pw_gid;
	pid_t pid = getpid();
	int au_cond;

	/* If we are not auditing, don't cut an audit record; just return. */
 	if (auditon(A_GETCOND, &au_cond, sizeof(au_cond)) < 0) {
		if (errno == ENOSYS)
			return;
		errx(1, "could not determine audit condition");
	}
	if (au_cond == AUC_NOAUDIT)
		return;

	/* Compute and set the user's preselection mask. */
	if (au_user_mask(pwd->pw_name, &aumask) == -1)
		errx(1, "could not calculate audit mask");

	/* Set the audit info for the user. */
	auinfo.ai_auid = uid;
	auinfo.ai_asid = pid;
	bcopy(&tid, &auinfo.ai_termid, sizeof(auinfo.ai_termid));
	bcopy(&aumask, &auinfo.ai_mask, sizeof(auinfo.ai_mask));
	if (setaudit(&auinfo) != 0)
		err(1, "setaudit failed");

	if ((aufd = au_open()) == -1)
		errx(1, "audit error: au_open() failed");

	if ((tok = au_to_subject32(uid, geteuid(), getegid(), uid, gid, pid,
	    pid, &tid)) == NULL)
		errx(1, "audit error: au_to_subject32() failed");
	au_write(aufd, tok);

	if ((tok = au_to_return32(0, 0)) == NULL)
		errx(1, "audit error: au_to_return32() failed");
	au_write(aufd, tok);

	if (au_close(aufd, 1, AUE_login) == -1)
		errx(1, "audit record was not committed.");
}