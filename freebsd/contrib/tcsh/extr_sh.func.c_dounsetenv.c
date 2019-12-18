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
struct command {int dummy; } ;
typedef  char Char ;

/* Variables and functions */
 int AsciiOnly ; 
 int /*<<< orphan*/  CTL_ESC (int) ; 
 int /*<<< orphan*/  Gmatch (char*,char*) ; 
 int /*<<< orphan*/  Isprint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LC_ALL ; 
 int /*<<< orphan*/  LC_COLLATE ; 
 int /*<<< orphan*/  LC_CTYPE ; 
 int /*<<< orphan*/  LC_MESSAGES ; 
 int MB_CUR_MAX ; 
 scalar_t__ MapsAreInited ; 
 scalar_t__ NLSMapsAreInited ; 
 scalar_t__ NoNLSRebind ; 
 int /*<<< orphan*/  STRLSCOLORS ; 
 int /*<<< orphan*/  STRLS_COLORS ; 
 int /*<<< orphan*/  STRNLSPATH ; 
 int /*<<< orphan*/  STRNOREBIND ; 
 int /*<<< orphan*/  STRSYSTYPE ; 
 char** STR_environ ; 
 int /*<<< orphan*/  STRtcshlang ; 
 int /*<<< orphan*/  USE (struct command*) ; 
 int /*<<< orphan*/  Unsetenv (char*) ; 
 int /*<<< orphan*/  cleanup_push (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_until (char*) ; 
 int /*<<< orphan*/  dohash (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dont_free ; 
 int /*<<< orphan*/  ed_Init () ; 
 int /*<<< orphan*/  ed_InitMaps () ; 
 int /*<<< orphan*/  ed_InitNLSMaps () ; 
 scalar_t__ eq (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fix_strcoll_bug () ; 
 int /*<<< orphan*/ * getenv (char*) ; 
 scalar_t__ islocale_var (char*) ; 
 int /*<<< orphan*/  nls_dll_unload () ; 
 int /*<<< orphan*/  nlsclose () ; 
 int /*<<< orphan*/  nlsinit () ; 
 int /*<<< orphan*/  parseLSCOLORS (char*) ; 
 int /*<<< orphan*/  parseLS_COLORS (char*) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tw_cmd_free () ; 
 int /*<<< orphan*/  xfree ; 
 char* xmalloc (int) ; 

void
dounsetenv(Char **v, struct command *c)
{
    Char  **ep, *p, *n, *name;
    int     i, maxi;

    USE(c);
    /*
     * Find the longest environment variable
     */
    for (maxi = 0, ep = STR_environ; *ep; ep++) {
	for (i = 0, p = *ep; *p && *p != '='; p++, i++)
	    continue;
	if (i > maxi)
	    maxi = i;
    }

    name = xmalloc((maxi + 1) * sizeof(Char));
    cleanup_push(name, xfree);

    while (++v && *v) 
	for (maxi = 1; maxi;)
	    for (maxi = 0, ep = STR_environ; *ep; ep++) {
		for (n = name, p = *ep; *p && *p != '='; *n++ = *p++)
		    continue;
		*n = '\0';
		if (!Gmatch(name, *v))
		    continue;
		maxi = 1;

		/* Unset the name. This wasn't being done until
		 * later but most of the stuff following won't
		 * work (particularly the setlocale() and getenv()
		 * stuff) as intended until the name is actually
		 * removed. (sg)
		 */
		Unsetenv(name);

		if (eq(name, STRNOREBIND)) {
		    NoNLSRebind = 0;
		    MapsAreInited = 0;
		    NLSMapsAreInited = 0;
		    ed_InitMaps();
		}
#ifdef apollo
		else if (eq(name, STRSYSTYPE))
		    dohash(NULL, NULL);
#endif /* apollo */
		else if (islocale_var(name)) {
#ifdef NLS
		    int     k;

# ifdef SETLOCALEBUG
		    dont_free = 1;
# endif /* SETLOCALEBUG */
		    (void) setlocale(LC_ALL, "");
# ifdef LC_COLLATE
		    (void) setlocale(LC_COLLATE, "");
# endif
# ifdef LC_CTYPE
		    (void) setlocale(LC_CTYPE, ""); /* for iscntrl */
# endif /* LC_CTYPE */
# ifdef NLS_CATALOGS
#  ifdef LC_MESSAGES
		    (void) setlocale(LC_MESSAGES, "");
#  endif /* LC_MESSAGES */
		    nlsclose();
		    nlsinit();
# endif /* NLS_CATALOGS */
# ifdef SETLOCALEBUG
		    dont_free = 0;
# endif /* SETLOCALEBUG */
# ifdef STRCOLLBUG
		    fix_strcoll_bug();
# endif /* STRCOLLBUG */
		    tw_cmd_free();/* since the collation sequence has changed */
		    for (k = 0200; k <= 0377 && !Isprint(CTL_ESC(k)); k++)
			continue;
		    AsciiOnly = MB_CUR_MAX == 1 && k > 0377;
#else /* !NLS */
		    AsciiOnly = getenv("LANG") == NULL &&
			getenv("LC_CTYPE") == NULL;
#endif /* NLS */
		    NLSMapsAreInited = 0;
		    ed_Init();
		    if (MapsAreInited && !NLSMapsAreInited)
			ed_InitNLSMaps();

		}
#ifdef WINNT_NATIVE
		else if (eq(name,(STRtcshlang))) {
		    nls_dll_unload();
		    nlsinit();
		}
#endif /* WINNT_NATIVE */
#ifdef COLOR_LS_F
		else if (eq(name, STRLS_COLORS))
		    parseLS_COLORS(n);
		else if (eq(name, STRLSCOLORS))
		    parseLSCOLORS(n);
#endif /* COLOR_LS_F */
#ifdef NLS_CATALOGS
		else if (eq(name, STRNLSPATH)) {
		    nlsclose();
		    nlsinit();
		}
#endif
		/*
		 * start again cause the environment changes
		 */
		break;
	    }
    cleanup_until(name);
}