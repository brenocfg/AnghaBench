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
struct stat {int dummy; } ;
struct Strbuf {scalar_t__ len; char* s; } ;
struct TYPE_2__ {char* di_name; } ;
typedef  char Char ;

/* Variables and functions */
 scalar_t__ ABSOLUTEP (char const*) ; 
 scalar_t__ ENOENT ; 
 scalar_t__ IS_DOT (char const*,char const*) ; 
 scalar_t__ IS_DOTDOT (char const*,char const*) ; 
 struct Strbuf Strbuf_INIT ; 
 int /*<<< orphan*/  Strbuf_append1 (struct Strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Strbuf_terminate (struct Strbuf*) ; 
 int /*<<< orphan*/  Strcpy (char*,char*) ; 
 int Strlen (char*) ; 
 char* Strrchr (char*,char) ; 
 char* Strsave (char const*) ; 
 char* Strspl (char*,char*) ; 
 char TRM (char) ; 
 TYPE_1__* dcwd ; 
 scalar_t__ errno ; 
 scalar_t__ lstat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  short2str (char const*) ; 
 scalar_t__ stat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  xfree (char*) ; 
 char* xmalloc (int) ; 

Char   *
dnormalize(const Char *cp, int expnd)
{

/* return true if dp is of the form "../xxx" or "/../xxx" */
#define IS_DOTDOT(sp, p) (ISDOTDOT(p) && ((p) == (sp) || *((p) - 1) == '/'))
#define IS_DOT(sp, p) (ISDOT(p) && ((p) == (sp) || *((p) - 1) == '/'))

#ifdef S_IFLNK
    if (expnd) {
	struct Strbuf buf = Strbuf_INIT;
 	int     dotdot = 0;
	Char   *dp, *cwd;
	const Char *start = cp;
# ifdef HAVE_SLASHSLASH
	int slashslash;
# endif /* HAVE_SLASHSLASH */

	/*
	 * count the number of "../xxx" or "xxx/../xxx" in the path
	 */
	for ( ; *cp && *(cp + 1); cp++)
	    if (IS_DOTDOT(start, cp))
	        dotdot++;

	/*
	 * if none, we are done.
	 */
        if (dotdot == 0)
	    return (Strsave(start));
	
# ifdef notdef
	struct stat sb;
	/*
	 * We disable this test because:
	 * cd /tmp; mkdir dir1 dir2; cd dir2; ln -s /tmp/dir1; cd dir1;
	 * echo ../../dir1 does not expand. We had enabled this before
	 * because it was bothering people with expansions in compilation
	 * lines like -I../../foo. Maybe we need some kind of finer grain
	 * control?
	 *
	 * If the path doesn't exist, we are done too.
	 */
	if (lstat(short2str(start), &sb) != 0 && errno == ENOENT)
	    return (Strsave(start));
# endif

	cwd = xmalloc((Strlen(dcwd->di_name) + 3) * sizeof(Char));
	(void) Strcpy(cwd, dcwd->di_name);

	/*
	 * If the path starts with a slash, we are not relative to
	 * the current working directory.
	 */
	if (ABSOLUTEP(start))
	    *cwd = '\0';
# ifdef HAVE_SLASHSLASH
	slashslash = cwd[0] == '/' && cwd[1] == '/';
# endif /* HAVE_SLASHSLASH */

	/*
	 * Ignore . and count ..'s
	 */
	cp = start;
	do {
	    dotdot = 0;
	    buf.len = 0;
	    while (*cp) 
	        if (IS_DOT(start, cp)) {
	            if (*++cp)
	                cp++;
	        }
	        else if (IS_DOTDOT(start, cp)) {
		    if (buf.len != 0)
		        break; /* finish analyzing .././../xxx/[..] */
		    dotdot++;
		    cp += 2;
		    if (*cp)
		        cp++;
	        }
	        else 
		    Strbuf_append1(&buf, *cp++);

	    Strbuf_terminate(&buf);
	    while (dotdot > 0) 
	        if ((dp = Strrchr(cwd, '/')) != NULL) {
# ifdef HAVE_SLASHSLASH
		    if (dp == &cwd[1]) 
		        slashslash = 1;
# endif /* HAVE_SLASHSLASH */
		        *dp = '\0';
		        dotdot--;
	        }
	        else
		    break;

	    if (!*cwd) {	/* too many ..'s, starts with "/" */
	        cwd[0] = '/';
# ifdef HAVE_SLASHSLASH
		/*
		 * Only append another slash, if already the former cwd
		 * was in a double-slash path.
		 */
		cwd[1] = slashslash ? '/' : '\0';
		cwd[2] = '\0';
# else /* !HAVE_SLASHSLASH */
		cwd[1] = '\0';
# endif /* HAVE_SLASHSLASH */
	    }
# ifdef HAVE_SLASHSLASH
	    else if (slashslash && cwd[1] == '\0') {
		cwd[1] = '/';
		cwd[2] = '\0';
	    }
# endif /* HAVE_SLASHSLASH */

	    if (buf.len != 0) {
		size_t i;

		i = Strlen(cwd);
		if (TRM(cwd[i - 1]) != '/') {
		    cwd[i++] = '/';
		    cwd[i] = '\0';
		}
	        dp = Strspl(cwd, TRM(buf.s[0]) == '/' ? &buf.s[1] : buf.s);
	        xfree(cwd);
	        cwd = dp;
		i = Strlen(cwd) - 1;
	        if (TRM(cwd[i]) == '/')
		    cwd[i] = '\0';
	    }
	    /* Reduction of ".." following the stuff we collected in buf
	     * only makes sense if the directory item in buf really exists.
	     * Avoid reduction of "-I../.." (typical compiler call) to ""
	     * or "/usr/nonexistant/../bin" to "/usr/bin":
	     */
	    if (cwd[0]) {
	        struct stat exists;
		if (0 != stat(short2str(cwd), &exists)) {
		    xfree(buf.s);
		    xfree(cwd);
		    return Strsave(start);
		}
	    }
	} while (*cp != '\0');
	xfree(buf.s);
	return cwd;
    }
#endif /* S_IFLNK */
    return Strsave(cp);
}