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
typedef  scalar_t__ time_t ;
struct varent {int /*<<< orphan*/ ** vec; } ;
struct stat {scalar_t__ st_mtime; scalar_t__ st_size; scalar_t__ st_atime; int /*<<< orphan*/  st_mode; } ;
struct TYPE_2__ {scalar_t__ tv_sec; } ;
typedef  int /*<<< orphan*/  DIR ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 char* CGETS (int,int,char*) ; 
 int MAILINTVL ; 
 int /*<<< orphan*/  STRmail ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 struct varent* adrof (int /*<<< orphan*/ ) ; 
 int blklen (int /*<<< orphan*/ **) ; 
 scalar_t__ chktim ; 
 int /*<<< orphan*/  cleanup_push (char*,int /*<<< orphan*/  (*) (char*)) ; 
 int /*<<< orphan*/  cleanup_until (char*) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getn (int /*<<< orphan*/ ) ; 
 scalar_t__ loginsh ; 
 scalar_t__ number (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 scalar_t__ readdir (int /*<<< orphan*/ *) ; 
 scalar_t__ seconds0 ; 
 char* short2str (int /*<<< orphan*/ *) ; 
 int stat (char*,struct stat*) ; 
 char* strsave (char*) ; 
 int /*<<< orphan*/  time (scalar_t__*) ; 
 TYPE_1__ time0 ; 
 char* xasprintf (char*,char*) ; 
 int /*<<< orphan*/  xfree (char*) ; 
 int /*<<< orphan*/  xprintf (char*,...) ; 

__attribute__((used)) static void
mailchk(void)
{
    struct varent *v;
    Char **vp;
    time_t  t;
    int     intvl, cnt;
    struct stat stb;
    int    new;

    v = adrof(STRmail);
    if (v == NULL || v->vec == NULL)
	return;
    (void) time(&t);
    vp = v->vec;
    cnt = blklen(vp);
    intvl = (cnt && number(*vp)) ? (--cnt, getn(*vp++)) : MAILINTVL;
    if (intvl < 1)
	intvl = 1;
    if (chktim + intvl > t)
	return;
    for (; *vp; vp++) {
	char *filename = short2str(*vp);
	char *mboxdir = filename;

	if (stat(filename, &stb) < 0)
	    continue;
#if defined(BSDTIMES) || defined(_SEQUENT_)
	new = stb.st_mtime > time0.tv_sec;
#else
	new = stb.st_mtime > seconds0;
#endif
	if (S_ISDIR(stb.st_mode)) {
	    DIR *mailbox;
	    int mailcount = 0;
	    char *tempfilename;
	    struct stat stc;

	    tempfilename = xasprintf("%s/new", filename);

	    if (stat(tempfilename, &stc) != -1 && S_ISDIR(stc.st_mode)) {
		/*
		 * "filename/new" exists and is a directory; you are
		 * using Qmail.
		 */
		stb = stc;
#if defined(BSDTIMES) || defined(_SEQUENT_)
		new = stb.st_mtime > time0.tv_sec;
#else
		new = stb.st_mtime > seconds0;
#endif
		mboxdir = tempfilename;
	    }

	    if (stb.st_mtime <= chktim + 1 || (loginsh && !new)) {
		xfree(tempfilename);
		continue;
	    }

	    mailbox = opendir(mboxdir);
	    xfree(tempfilename);
	    if (mailbox == NULL)
		continue;

	    /* skip . and .. */
	    if (!readdir(mailbox) || !readdir(mailbox)) {
		(void)closedir(mailbox);
		continue;
	    }

	    while (readdir(mailbox))
		mailcount++;

	    (void)closedir(mailbox);
	    if (mailcount == 0)
		continue;

	    if (cnt == 1)
		xprintf(CGETS(11, 3, "You have %d mail messages.\n"),
			mailcount);
	    else
		xprintf(CGETS(11, 4, "You have %d mail messages in %s.\n"),
			mailcount, filename);
	}
	else {
	    char *type;
	    
	    if (stb.st_size == 0 || stb.st_atime >= stb.st_mtime ||
		(stb.st_atime <= chktim && stb.st_mtime <= chktim) ||
		(loginsh && !new))
		continue;
	    type = strsave(new ? CGETS(11, 6, "new ") : "");
	    cleanup_push(type, xfree);
	    if (cnt == 1)
		xprintf(CGETS(11, 5, "You have %smail.\n"), type);
	    else
	        xprintf(CGETS(11, 7, "You have %smail in %s.\n"), type, filename);
	    cleanup_until(type);
	}
    }
    chktim = t;
}