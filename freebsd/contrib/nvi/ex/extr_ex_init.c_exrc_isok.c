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
typedef  scalar_t__ uid_t ;
struct stat {scalar_t__ st_uid; int st_mode; } ;
typedef  enum rc { ____Placeholder_rc } rc ;
typedef  int /*<<< orphan*/  SCR ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_SPACE (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_ERR ; 
 int /*<<< orphan*/  M_SYSERR ; 
 int NOEXIST ; 
 int NOPERM ; 
 int RCOK ; 
 int S_IWGRP ; 
 int S_IWOTH ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getcwd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ geteuid () ; 
 char* join (char*,char*) ; 
 char* msg_print (int /*<<< orphan*/ *,char*,int*) ; 
 int /*<<< orphan*/  msgq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 

__attribute__((used)) static enum rc
exrc_isok(SCR *sp, struct stat *sbp, char *path, int rootown, int rootid)
{
	enum { ROOTOWN, OWN, WRITER } etype;
	uid_t euid;
	int nf1, nf2;
	char *a, *b, *buf;

	/* Check for the file's existence. */
	if (stat(path, sbp))
		return (NOEXIST);

	/* Check ownership permissions. */
	euid = geteuid();
	if (!(rootown && sbp->st_uid == 0) &&
	    !(rootid && euid == 0) && sbp->st_uid != euid) {
		etype = rootown ? ROOTOWN : OWN;
		goto denied;
	}

	/* Check writeability. */
	if (sbp->st_mode & (S_IWGRP | S_IWOTH)) {
		etype = WRITER;
		goto denied;
	}
	return (RCOK);

denied:	a = msg_print(sp, path, &nf1);
	if (strchr(path, '/') == NULL && (buf = getcwd(NULL, 0)) != NULL) {
		char *p;

		b = msg_print(sp, buf, &nf2);
		if ((p = join(b, a)) == NULL) {
			msgq(sp, M_SYSERR, NULL);
			goto err;
		}
		switch (etype) {
		case ROOTOWN:
			msgq(sp, M_ERR,
			    "128|%s: not sourced: not owned by you or root", p);
			break;
		case OWN:
			msgq(sp, M_ERR,
			    "129|%s: not sourced: not owned by you", p);
			break;
		case WRITER:
			msgq(sp, M_ERR,
    "130|%s: not sourced: writeable by a user other than the owner", p);
			break;
		}
		free(p);
err:		free(buf);
		if (nf2)
			FREE_SPACE(sp, b, 0);
	} else
		switch (etype) {
		case ROOTOWN:
			msgq(sp, M_ERR,
			    "128|%s: not sourced: not owned by you or root", a);
			break;
		case OWN:
			msgq(sp, M_ERR,
			    "129|%s: not sourced: not owned by you", a);
			break;
		case WRITER:
			msgq(sp, M_ERR,
	    "130|%s: not sourced: writeable by a user other than the owner", a);
			break;
		}

	if (nf1)
		FREE_SPACE(sp, a, 0);
	return (NOPERM);
}