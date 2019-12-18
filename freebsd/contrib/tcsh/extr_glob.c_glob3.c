#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct strbuf {size_t len; scalar_t__* s; } ;
struct stat {int /*<<< orphan*/  st_mode; } ;
struct dirent {scalar_t__* d_name; } ;
struct TYPE_4__ {int gl_flags; scalar_t__ (* gl_errfunc ) (scalar_t__*,int) ;} ;
typedef  TYPE_1__ glob_t ;
typedef  int /*<<< orphan*/  __Char ;
typedef  int /*<<< orphan*/  DIR ;
typedef  scalar_t__ Char ;

/* Variables and functions */
 scalar_t__ DOT ; 
 scalar_t__ const EOS ; 
 int GLOB_ABEND ; 
 int GLOB_ALTNOT ; 
 int GLOB_DOT ; 
 int GLOB_ERR ; 
 scalar_t__ Lstat (scalar_t__*,struct stat*) ; 
 int /*<<< orphan*/  MB_LEN_MAX ; 
 scalar_t__ const M_ALL ; 
 scalar_t__ M_ALTNOT ; 
 scalar_t__ const M_MASK ; 
 scalar_t__ M_NOT ; 
 size_t One_Char_mbtowc (int /*<<< orphan*/ *,scalar_t__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Opendir (scalar_t__*) ; 
 int /*<<< orphan*/  SEP ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int errno ; 
 int glob2 (struct strbuf*,scalar_t__ const*,TYPE_1__*,int) ; 
 int match (scalar_t__*,scalar_t__ const*,scalar_t__ const*,int) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_append (struct strbuf*,scalar_t__*) ; 
 int /*<<< orphan*/  strbuf_append1 (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_terminate (struct strbuf*) ; 
 scalar_t__ stub1 (scalar_t__*,int) ; 

__attribute__((used)) static int
glob3(struct strbuf *pathbuf, const Char *pattern, const Char *restpattern,
      const Char *pglobstar, glob_t *pglob, int no_match)
{
    DIR    *dirp;
    struct dirent *dp;
    struct stat sbuf;
    int     err;
    Char m_not = (pglob->gl_flags & GLOB_ALTNOT) ? M_ALTNOT : M_NOT;
    size_t orig_len;
    int globstar = 0;
    int chase_symlinks = 0;
    const Char *termstar = NULL;

    strbuf_terminate(pathbuf);
    orig_len = pathbuf->len;
    errno = err = 0;

    while (pglobstar < restpattern) {
	__Char wc;
	size_t width = One_Char_mbtowc(&wc, pglobstar, MB_LEN_MAX);
	if ((pglobstar[0] & M_MASK) == M_ALL &&
	    (pglobstar[width] & M_MASK) == M_ALL) {
	    globstar = 1;
	    chase_symlinks = (pglobstar[2 * width] & M_MASK) == M_ALL;
	    termstar = pglobstar + (2 + chase_symlinks) * width;
	    break;
	}
        pglobstar += width;
    } 

    if (globstar) {
	err = pglobstar==pattern && termstar==restpattern ?
		*restpattern == EOS ?
		glob2(pathbuf, restpattern - 1, pglob, no_match) :
		glob2(pathbuf, restpattern + 1, pglob, no_match) :
		glob3(pathbuf, pattern, restpattern, termstar, pglob, no_match);
	if (err)
	    return err;
	pathbuf->len = orig_len;
	strbuf_terminate(pathbuf);
    }

    if (*pathbuf->s && (Lstat(pathbuf->s, &sbuf) || !S_ISDIR(sbuf.st_mode)
#ifdef S_IFLINK
	     && ((globstar && !chase_symlinks) || !S_ISLNK(sbuf.st_mode))
#endif
	))
	return 0;

    if (!(dirp = Opendir(pathbuf->s))) {
	/* todo: don't call for ENOENT or ENOTDIR? */
	if ((pglob->gl_errfunc && (*pglob->gl_errfunc) (pathbuf->s, errno)) ||
	    (pglob->gl_flags & GLOB_ERR))
	    return (GLOB_ABEND);
	else
	    return (0);
    }

    /* search directory for matching names */
    while ((dp = readdir(dirp)) != NULL) {
	/* initial DOT must be matched literally */
	if (dp->d_name[0] == DOT && *pattern != DOT)
	    if (!(pglob->gl_flags & GLOB_DOT) || !dp->d_name[1] ||
		(dp->d_name[1] == DOT && !dp->d_name[2]))
		continue; /*unless globdot and not . or .. */
	pathbuf->len = orig_len;
	strbuf_append(pathbuf, dp->d_name);
	strbuf_terminate(pathbuf);

	if (globstar) {
#ifdef S_IFLNK
	    if (!chase_symlinks &&
		(Lstat(pathbuf->s, &sbuf) || S_ISLNK(sbuf.st_mode)))
		    continue;
#endif
	    if (match(pathbuf->s + orig_len, pattern, termstar,
		(int)m_not) == no_match) 
		    continue;
	    strbuf_append1(pathbuf, SEP);
	    strbuf_terminate(pathbuf);
	    if ((err = glob2(pathbuf, pglobstar, pglob, no_match)) != 0)
		break;
	} else {
	    if (match(pathbuf->s + orig_len, pattern, restpattern,
		(int) m_not) == no_match)
		continue;
	    if ((err = glob2(pathbuf, restpattern, pglob, no_match)) != 0)
		break;
	}
    }
    /* todo: check error from readdir? */
    closedir(dirp);
    return (err);
}