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
typedef  int /*<<< orphan*/  time_t ;
typedef  int tcsh_number_t ;
struct stat {int st_mode; int st_dm_key; int st_dmonflags; int /*<<< orphan*/  st_ctime; int /*<<< orphan*/  st_mtime; int /*<<< orphan*/  st_atime; int /*<<< orphan*/  st_size; int /*<<< orphan*/  st_gid; int /*<<< orphan*/  st_uid; int /*<<< orphan*/  st_nlink; scalar_t__ st_ino; scalar_t__ st_dev; int /*<<< orphan*/  st_dm_mode; } ;
struct passwd {char* pw_name; } ;
struct group {char* gr_name; } ;
struct cvxstat {int dummy; } ;
typedef  int /*<<< orphan*/  string0 ;
typedef  char Char ;

/* Variables and functions */
 int /*<<< orphan*/  ANYOP ; 
 int ERR_FILEINQ ; 
 int ERR_FILENAME ; 
 int ERR_NAME ; 
 char* FILETESTS ; 
 char* FILEVALS ; 
 int /*<<< orphan*/  G_APPEND ; 
 int IMIGRATED ; 
 int /*<<< orphan*/  MB_LEN_MAX ; 
 int /*<<< orphan*/  R_OK ; 
 char* STR0 ; 
 char* STRNULL ; 
 char* STRcolon ; 
 char* STRminus1 ; 
 int S_IRWXG ; 
 int S_IRWXO ; 
 int S_IRWXU ; 
 int S_ISBLK (int) ; 
 int S_ISCHR (int) ; 
 int S_ISDIR (int) ; 
 int S_ISFIFO (int) ; 
 int S_ISGID ; 
 int S_ISLNK (int) ; 
 int S_ISOFL (int /*<<< orphan*/ ) ; 
 int S_ISREG (int) ; 
 int S_ISSOCK (int) ; 
 int S_ISUID ; 
 int S_ISVTX ; 
 int /*<<< orphan*/  Strcat (int /*<<< orphan*/ ,char*) ; 
 char* Strchr (char*,char) ; 
 scalar_t__ Strcmp (char*,char*) ; 
 int /*<<< orphan*/  Strcpy (char*,char*) ; 
 int Strlen (char*) ; 
 char* Strsave (char*) ; 
 int TCSH_LSTAT (char*,struct stat*) ; 
 int TCSH_STAT (char*,struct stat*) ; 
 int TEXP_IGNORE ; 
 int /*<<< orphan*/  W_OK ; 
 int /*<<< orphan*/  X_OK ; 
 scalar_t__ any (char*,char) ; 
 char* areadlink (char*) ; 
 int /*<<< orphan*/  atoi (char*) ; 
 int /*<<< orphan*/  cleanup_push (char*,int /*<<< orphan*/  (*) (char*)) ; 
 int /*<<< orphan*/  cleanup_until (char*) ; 
 char* ctime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  etraci (char*,int,char***) ; 
 int find_cmd (char*,int /*<<< orphan*/ ) ; 
 char* globone (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ isa (char*,int /*<<< orphan*/ ) ; 
 int isatty (int /*<<< orphan*/ ) ; 
 char* putn (int) ; 
 int /*<<< orphan*/  sh_access (char*,int /*<<< orphan*/ ) ; 
 char* short2str (char*) ; 
 int /*<<< orphan*/  stderror (int) ; 
 char* str2short (char*) ; 
 char tolower (char) ; 
 int /*<<< orphan*/  uid ; 
 int /*<<< orphan*/  xfree (char*) ; 
 struct group* xgetgrgid (int /*<<< orphan*/ ) ; 
 struct passwd* xgetpwuid (int /*<<< orphan*/ ) ; 
 char* xmalloc (int) ; 
 int /*<<< orphan*/  xsnprintf (char*,int,char*,unsigned int) ; 

Char *
filetest(Char *cp, Char ***vp, int ignore)
{
#ifdef convex
    struct cvxstat stb, *st = NULL;
# define TCSH_STAT	stat64
#else
# define TCSH_STAT	stat
    struct stat stb, *st = NULL;
#endif /* convex */

#ifdef S_IFLNK
# ifdef convex
    struct cvxstat lstb, *lst = NULL;
#  define TCSH_LSTAT lstat64
# else
#  define TCSH_LSTAT lstat
    struct stat lstb, *lst = NULL;
# endif /* convex */
    char *filnam;
#endif /* S_IFLNK */

    tcsh_number_t i = 0;
    unsigned pmask = 0xffff;
    int altout = 0;
    Char *ft = cp, *dp, *ep, *strdev, *strino, *strF, *str, valtest = '\0',
    *errval = STR0;
    char *string, string0[22 + MB_LEN_MAX + 1];	/* space for 64 bit octal */
    time_t footime;
    struct passwd *pw;
    struct group *gr;

    while(any(FILETESTS, *++ft))
	continue;

    if (!*ft && *(ft - 1) == 'L')
	--ft;

    if (any(FILEVALS, *ft)) {
	valtest = *ft++;
	/*
	 * Value tests return '-1' on failure as 0 is
	 * a legitimate value for many of them.
	 * 'F' returns ':' for compatibility.
	 */
	errval = valtest == 'F' ? STRcolon : STRminus1;

	if (valtest == 'P' && *ft >= '0' && *ft <= '7') {
	    pmask = (char) *ft - '0';
	    while ( *++ft >= '0' && *ft <= '7' )
		pmask = 8 * pmask + ((char) *ft - '0');
	}
	if (Strcmp(ft, STRcolon) == 0 && any("AMCUGP", valtest)) {
	    altout = 1;
	    ++ft;
	}
    }

    if (*ft || ft == cp + 1)
	stderror(ERR_NAME | ERR_FILEINQ);

    /*
     * Detect missing file names by checking for operator in the file name
     * position.  However, if an operator name appears there, we must make
     * sure that there's no file by that name (e.g., "/") before announcing
     * an error.  Even this check isn't quite right, since it doesn't take
     * globbing into account.
     */

    if (isa(**vp, ANYOP) && TCSH_STAT(short2str(**vp), &stb))
	stderror(ERR_NAME | ERR_FILENAME);

    dp = *(*vp)++;
    if (ignore & TEXP_IGNORE)
	return (Strsave(STRNULL));
    ep = globone(dp, G_APPEND);
    cleanup_push(ep, xfree);
    ft = &cp[1];
    do 
	switch (*ft) {

	case 'r':
	    i = !sh_access(ep, R_OK);
	    break;

	case 'w':
	    i = !sh_access(ep, W_OK);
	    break;

	case 'x':
	    i = !sh_access(ep, X_OK);
	    break;

	case 'X':	/* tcsh extension, name is an executable in the path
			 * or a tcsh builtin command 
			 */
	    i = find_cmd(ep, 0);
	    break;

	case 't':	/* SGI extension, true when file is a tty */
	    i = isatty(atoi(short2str(ep)));
	    break;

	default:

#ifdef S_IFLNK
	    if (tolower(*ft) == 'l') {
		/* 
		 * avoid convex compiler bug.
		 */
		if (!lst) {
		    lst = &lstb;
		    if (TCSH_LSTAT(short2str(ep), lst) == -1) {
			cleanup_until(ep);
			return (Strsave(errval));
		    }
		}
		if (*ft == 'L')
		    st = lst;
	    }
	    else 
#endif /* S_IFLNK */
		/* 
		 * avoid convex compiler bug.
		 */
		if (!st) {
		    st = &stb;
		    if (TCSH_STAT(short2str(ep), st) == -1) {
			cleanup_until(ep);
			return (Strsave(errval));
		    }
		}

	    switch (*ft) {

	    case 'f':
#ifdef S_ISREG
		i = S_ISREG(st->st_mode);
#else /* !S_ISREG */
		i = 0;
#endif /* S_ISREG */
		break;

	    case 'd':
#ifdef S_ISDIR
		i = S_ISDIR(st->st_mode);
#else /* !S_ISDIR */
		i = 0;
#endif /* S_ISDIR */
		break;

	    case 'p':
#ifdef S_ISFIFO
		i = S_ISFIFO(st->st_mode);
#else /* !S_ISFIFO */
		i = 0;
#endif /* S_ISFIFO */
		break;

	    case 'm' :
#ifdef S_ISOFL
	      i = S_ISOFL(st->st_dm_mode);
#else /* !S_ISOFL */
	      i = 0;
#endif /* S_ISOFL */
	      break ;

	    case 'K' :
#ifdef S_ISOFL
	      i = stb.st_dm_key;
#else /* !S_ISOFL */
	      i = 0;
#endif /* S_ISOFL */
	      break ;
  

	    case 'l':
#ifdef S_ISLNK
		i = S_ISLNK(lst->st_mode);
#else /* !S_ISLNK */
		i = 0;
#endif /* S_ISLNK */
		break;

	    case 'S':
# ifdef S_ISSOCK
		i = S_ISSOCK(st->st_mode);
# else /* !S_ISSOCK */
		i = 0;
# endif /* S_ISSOCK */
		break;

	    case 'b':
#ifdef S_ISBLK
		i = S_ISBLK(st->st_mode);
#else /* !S_ISBLK */
		i = 0;
#endif /* S_ISBLK */
		break;

	    case 'c':
#ifdef S_ISCHR
		i = S_ISCHR(st->st_mode);
#else /* !S_ISCHR */
		i = 0;
#endif /* S_ISCHR */
		break;

	    case 'u':
		i = (S_ISUID & st->st_mode) != 0;
		break;

	    case 'g':
		i = (S_ISGID & st->st_mode) != 0;
		break;

	    case 'k':
		i = (S_ISVTX & st->st_mode) != 0;
		break;

	    case 'z':
		i = st->st_size == 0;
		break;

#ifdef convex
	    case 'R':
		i = (stb.st_dmonflags & IMIGRATED) == IMIGRATED;
		break;
#endif /* convex */

	    case 's':
		i = stb.st_size != 0;
		break;

	    case 'e':
		i = 1;
		break;

	    case 'o':
		i = st->st_uid == uid;
		break;

		/*
		 * Value operators are a tcsh extension.
		 */

	    case 'D':
		i = (tcsh_number_t) st->st_dev;
		break;

	    case 'I':
		i = (tcsh_number_t) st->st_ino;
		break;
		
	    case 'F':
		strdev = putn( (int) st->st_dev);
		strino = putn( (int) st->st_ino);
		strF = xmalloc((2 + Strlen(strdev) + Strlen(strino))
			       * sizeof(Char));
		(void) Strcat(Strcat(Strcpy(strF, strdev), STRcolon), strino);
		xfree(strdev);
		xfree(strino);
		cleanup_until(ep);
		return(strF);
		
	    case 'L':
		if ( *(ft + 1) ) {
		    i = 1;
		    break;
		}
#ifdef S_ISLNK
		filnam = short2str(ep);
		string = areadlink(filnam);
		strF = string == NULL ? errval : str2short(string);
		xfree(string);
		cleanup_until(ep);
		return(Strsave(strF));

#else /* !S_ISLNK */
		i = 0;
		break;
#endif /* S_ISLNK */
		

	    case 'N':
		i = (tcsh_number_t) st->st_nlink;
		break;

	    case 'P':
		string = string0 + 1;
		(void) xsnprintf(string, sizeof(string0) - 1, "%o",
		    pmask & (unsigned int) 
		    ((S_IRWXU|S_IRWXG|S_IRWXO|S_ISUID|S_ISGID) & st->st_mode));
		if (altout && *string != '0')
		    *--string = '0';
		cleanup_until(ep);
		return(Strsave(str2short(string)));

	    case 'U':
		if (altout && (pw = xgetpwuid(st->st_uid))) {
		    cleanup_until(ep);
		    return(Strsave(str2short(pw->pw_name)));
		}
		i = (tcsh_number_t) st->st_uid;
		break;

	    case 'G':
		if (altout && (gr = xgetgrgid(st->st_gid))) {
		    cleanup_until(ep);
		    return(Strsave(str2short(gr->gr_name)));
		}
		i = (tcsh_number_t) st->st_gid;
		break;

	    case 'Z':
		i = (tcsh_number_t) st->st_size;
		break;

	    case 'A': case 'M': case 'C':
		footime = *ft == 'A' ? st->st_atime :
		    *ft == 'M' ? st->st_mtime : st->st_ctime;
		if (altout) {
		    strF = str2short(ctime(&footime));
		    if ((str = Strchr(strF, '\n')) != NULL)
			*str = (Char) '\0';
		    cleanup_until(ep);
		    return(Strsave(strF));
		}
		i = (tcsh_number_t) footime;
		break;

	    }
	}
    while (*++ft && i);
    etraci("exp6 -? i", i, vp);
    cleanup_until(ep);
    return (putn(i));
}