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
typedef  int /*<<< orphan*/  uid_t ;
typedef  int /*<<< orphan*/  token_t ;
struct auditinfo_addr {int /*<<< orphan*/  ai_termid; } ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  aia ;

/* Variables and functions */
 int ADE_AU_CLOSE ; 
 int ADE_AU_OPEN ; 
 int ADE_INVAL ; 
 int ADE_NOERR ; 
 int ADE_NOMEM ; 
 int AUE_audit_recovery ; 
 int AUE_audit_shutdown ; 
 int AUE_audit_startup ; 
 int /*<<< orphan*/  asprintf (char**,char*,int /*<<< orphan*/ ) ; 
 int au_close (int,int,int) ; 
 int au_open () ; 
 int /*<<< orphan*/ * au_to_path (char*) ; 
 int /*<<< orphan*/ * au_to_return32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * au_to_subject32_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * au_to_text (char*) ; 
 int /*<<< orphan*/  au_write (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bzero (struct auditinfo_addr*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  getegid () ; 
 int /*<<< orphan*/  geteuid () ; 
 int /*<<< orphan*/  getgid () ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  getprogname () ; 
 int /*<<< orphan*/  getuid () ; 

int
auditd_gen_record(int event, char *path)
{
	int aufd;
	uid_t uid;
	pid_t pid;
	char *autext = NULL;
	token_t *tok;
	struct auditinfo_addr aia;

	if (event == AUE_audit_startup)
		asprintf(&autext, "%s::Audit startup", getprogname());
	else if (event == AUE_audit_shutdown)
		asprintf(&autext, "%s::Audit shutdown", getprogname());
	else if (event == AUE_audit_recovery)
		asprintf(&autext, "%s::Audit recovery", getprogname());
	else
		return (ADE_INVAL);
	if (autext == NULL)
		return (ADE_NOMEM);

	if ((aufd = au_open()) == -1) {
		free(autext);
		return (ADE_AU_OPEN);
	}
	bzero(&aia, sizeof(aia));
	uid = getuid(); pid = getpid();
	if ((tok = au_to_subject32_ex(uid, geteuid(), getegid(), uid, getgid(),
	    pid, pid, &aia.ai_termid)) != NULL)
		au_write(aufd, tok);
	if ((tok = au_to_text(autext)) != NULL)
		au_write(aufd, tok);
	free(autext);
	if (path != NULL && (tok = au_to_path(path)) != NULL)
		au_write(aufd, tok);
	if ((tok = au_to_return32(0, 0)) != NULL)
		au_write(aufd, tok);
	if (au_close(aufd, 1, event) == -1)
		return (ADE_AU_CLOSE);

	return (ADE_NOERR);
}