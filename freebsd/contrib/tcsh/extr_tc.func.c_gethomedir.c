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
struct passwd {char* pw_dir; } ;
typedef  char Char ;

/* Variables and functions */
 char* Strsave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fix_yp_bugs () ; 
 int /*<<< orphan*/  free (char*) ; 
 char** hes_resolve (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  short2str (char const*) ; 
 int /*<<< orphan*/  str2short (char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strtok (char*,char*) ; 
 int /*<<< orphan*/  xfree (char*) ; 
 struct passwd* xgetpwnam (int /*<<< orphan*/ ) ; 

__attribute__((used)) static Char *
gethomedir(const Char *us)
{
    struct passwd *pp;
#ifdef HESIOD
    char **res, **res1, *cp;
    Char *rp;
#endif /* HESIOD */
    
    pp = xgetpwnam(short2str(us));
#ifdef YPBUGS
    fix_yp_bugs();
#endif /* YPBUGS */
    if (pp != NULL) {
#if 0
	/* Don't return if root */
	if (pp->pw_dir[0] == '/' && pp->pw_dir[1] == '\0')
	    return NULL;
	else
#endif
	    return Strsave(str2short(pp->pw_dir));
    }
#ifdef HESIOD
    res = hes_resolve(short2str(us), "filsys");
    rp = NULL;
    if (res != NULL) {
	if ((*res) != NULL) {
	    /*
	     * Look at the first token to determine how to interpret
	     * the rest of it.
	     * Yes, strtok is evil (it's not thread-safe), but it's also
	     * easy to use.
	     */
	    cp = strtok(*res, " ");
	    if (strcmp(cp, "AFS") == 0) {
		/* next token is AFS pathname.. */
		cp = strtok(NULL, " ");
		if (cp != NULL)
		    rp = Strsave(str2short(cp));
	    } else if (strcmp(cp, "NFS") == 0) {
		cp = NULL;
		if ((strtok(NULL, " ")) && /* skip remote pathname */
		    (strtok(NULL, " ")) && /* skip host */
		    (strtok(NULL, " ")) && /* skip mode */
		    (cp = strtok(NULL, " "))) {
		    rp = Strsave(str2short(cp));
		}
	    }
	}
	for (res1 = res; *res1; res1++)
	    free(*res1);
#if 0
	/* Don't return if root */
	if (rp != NULL && rp[0] == '/' && rp[1] == '\0') {
	    xfree(rp);
	    rp = NULL;
	}
#endif
	return rp;
    }
#endif /* HESIOD */
    return NULL;
}