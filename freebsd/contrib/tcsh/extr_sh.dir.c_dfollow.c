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
struct varent {char** vec; } ;
struct Strbuf {char* s; int /*<<< orphan*/  len; } ;
typedef  char Char ;

/* Variables and functions */
 int ENOENT ; 
 int ENOTDIR ; 
 int /*<<< orphan*/  ERR_SYSTEM ; 
 int /*<<< orphan*/  G_ERROR ; 
 int /*<<< orphan*/  STRcdpath ; 
 int /*<<< orphan*/  STRdotdotsl ; 
 int /*<<< orphan*/  STRdotsl ; 
 scalar_t__ SYM_EXPAND ; 
 scalar_t__ SYM_IGNORE ; 
 struct Strbuf Strbuf_INIT ; 
 int /*<<< orphan*/  Strbuf_append (struct Strbuf*,char*) ; 
 int /*<<< orphan*/  Strbuf_append1 (struct Strbuf*,char) ; 
 int /*<<< orphan*/  Strbuf_terminate (struct Strbuf*) ; 
 scalar_t__ Strchr (char*,char) ; 
 size_t Strlen (char*) ; 
 char* Strsave (char*) ; 
 struct varent* adrof (int /*<<< orphan*/ ) ; 
 char* agetcwd () ; 
 int /*<<< orphan*/  bequiet ; 
 scalar_t__ chdir (char*) ; 
 int /*<<< orphan*/  cleanup_ignore (char*) ; 
 int /*<<< orphan*/  cleanup_push (char*,int /*<<< orphan*/  (*) (char*)) ; 
 int /*<<< orphan*/  cleanup_until (char*) ; 
 char* dgoto (char*) ; 
 char* dnormalize (char*,int) ; 
 int errno ; 
 char* globone (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prefix (int /*<<< orphan*/ ,char*) ; 
 int printd ; 
 char* short2str (char*) ; 
 int /*<<< orphan*/  stderror (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int) ; 
 scalar_t__ symlinks ; 
 char* varval (char*) ; 
 int /*<<< orphan*/  xfree (char*) ; 

__attribute__((used)) static Char *
dfollow(Char *cp, int old)
{
    Char *dp;
    struct varent *c;
    int serrno;

    cp = old ? Strsave(cp) : globone(cp, G_ERROR);
    cleanup_push(cp, xfree);
#ifdef apollo
    if (Strchr(cp, '`')) {
	char *dptr;
	if (chdir(dptr = short2str(cp)) < 0) 
	    stderror(ERR_SYSTEM, dptr, strerror(errno));
	dp = agetcwd();
	cleanup_push(dp, xfree);
	if (dp != NULL) {
	    cleanup_until(cp);
	    return dgoto(dp);
	}
	else
	    stderror(ERR_SYSTEM, dptr, strerror(errno));
    }
#endif /* apollo */

    /*
     * if we are ignoring symlinks, try to fix relatives now.
     * if we are expading symlinks, it should be done by now.
     */ 
    dp = dnormalize(cp, symlinks == SYM_IGNORE);
    if (chdir(short2str(dp)) >= 0) {
        cleanup_until(cp);
        return dgoto(dp);
    }
    else {
        xfree(dp);
        if (chdir(short2str(cp)) >= 0) {
	    cleanup_ignore(cp);
	    cleanup_until(cp);
	    return dgoto(cp);
	}
	else if (errno != ENOENT && errno != ENOTDIR) {
	    int err;

	    err = errno;
	    stderror(ERR_SYSTEM, short2str(cp), strerror(err));
	}
	serrno = errno;
    }

    if (cp[0] != '/' && !prefix(STRdotsl, cp) && !prefix(STRdotdotsl, cp)
	&& (c = adrof(STRcdpath)) && c->vec != NULL) {
	struct Strbuf buf = Strbuf_INIT;
	Char  **cdp;

	for (cdp = c->vec; *cdp; cdp++) {
	    size_t len = Strlen(*cdp);
	    buf.len = 0;
	    if (len > 0) {
		Strbuf_append(&buf, *cdp);
		if ((*cdp)[len - 1] != '/')
		    Strbuf_append1(&buf, '/');
	    }
	    Strbuf_append(&buf, cp);
	    Strbuf_terminate(&buf);
	    /*
	     * We always want to fix the directory here
	     * If we are normalizing symlinks
	     */
	    dp = dnormalize(buf.s, symlinks == SYM_IGNORE || 
				   symlinks == SYM_EXPAND);
	    if (chdir(short2str(dp)) >= 0) {
		printd = 1;
		xfree(buf.s);
		cleanup_until(cp);
		return dgoto(dp);
	    }
	    else if (chdir(short2str(cp)) >= 0) {
		printd = 1;
		xfree(dp);
		xfree(buf.s);
		cleanup_ignore(cp);
		cleanup_until(cp);
		return dgoto(cp);
	    }
	    xfree(dp);
	}
	xfree(buf.s);
    }
    dp = varval(cp);
    if ((dp[0] == '/' || dp[0] == '.') && chdir(short2str(dp)) >= 0) {
	cleanup_until(cp);
	cp = Strsave(dp);
	printd = 1;
	return dgoto(cp);
    }
    /*
     * on login source of ~/.cshdirs, errors are eaten. the dir stack is all
     * directories we could get to.
     */
    if (!bequiet)
	stderror(ERR_SYSTEM, short2str(cp), strerror(serrno));
    cleanup_until(cp);
    return (NULL);
}